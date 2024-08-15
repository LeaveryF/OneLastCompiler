#pragma once

#include <olc/Support.h>

#include <olc/backend/MachineIR.h>
#include <olc/backend/RegAlloc.h>
#include <olc/ir/IR.h>

#include <map>

namespace olc {

struct ArmGen {

  std::ostream &os;
  AsmModule *module = nullptr;
  AsmFunc *curFunc = nullptr;
  std::unordered_map<AsmLabel *, int> labelMap;

  ArmGen(std::ostream &os, AsmModule *module) : os(os), module(module) {}

  std::string getCondStr(AsmPredicate pred) {
    switch (pred) {
    case AsmPredicate::Al:
      return "al";
    case AsmPredicate::Eq:
      return "eq";
    case AsmPredicate::Ne:
      return "ne";
    case AsmPredicate::Lt:
      return "lt";
    case AsmPredicate::Le:
      return "le";
    case AsmPredicate::Gt:
      return "gt";
    case AsmPredicate::Ge:
      return "ge";
    default:
      olc_unreachable("Unknown condition");
    }
  }

  void printArmInstr(
      const std::string &op, const std::vector<std::string> &operands) {

    // indent for instructions
    os << "  ";

    os << op;
    os << " ";
    for (int i = 0; i < operands.size(); ++i) {
      if (i > 0) {
        os << ", ";
      }
      os << operands[i];
    }
    os << '\n';
  }

  std::string getLabel(AsmLabel *label) {
    if (labelMap.find(label) == labelMap.end()) {
      labelMap[label] = labelMap.size();
    }
    return "." + label->name + "_" + std::to_string(labelMap[label]);
  }

  void runRegAlloc() {
    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;
      LinearScan regAlloc;
      regAlloc.runOnFunction(func);
      auto &regMap = regAlloc.regMap;
      std::map<AsmReg *, int> spillMap;

      for (auto *var : regAlloc.spills) {
        spillMap[var] = func->stackSize;
        func->stackSize += 4;
      }

      auto generateSpillAddress = [](AsmAccess *access, int offset) {
        if (offset < 4096) {
          access->addr = PReg::sp();
          access->offset = new AsmImm{static_cast<uint32_t>(offset)};
        } else {
          olc_unreachable("big offset NYI");
        }
      };

      for (auto *label : func->labels) {
        for (auto *inst = label->Head; inst != nullptr; inst = inst->Next) {
          for (auto refdef : inst->getDefs()) {
            auto &def = *refdef;
            assert(isa<AsmReg>(def) && "Non-reg def!");
            if (auto *preg = dyn_cast<PReg>(def)) {
              continue;
            } else if (auto *vreg = dyn_cast<VReg>(def)) {
              if (auto it = regMap.find(vreg); it != regMap.end()) {
                def = it->second;
              } else if (regAlloc.spills.count(vreg)) {
                // spill it with str lr
                def = PReg::lr();
                int offset = spillMap.at(vreg);
                auto storeSlotInst = new AsmStoreInst{};
                generateSpillAddress(storeSlotInst, offset);
                storeSlotInst->src = def;
                label->push_after(inst, storeSlotInst);
              }
            } else {
              olc_unreachable("Invalid asm reg for def");
            }
          }

          for (auto refuse : inst->getUses()) {
            auto &use = *refuse;
            if (auto *vreg = dyn_cast_if_present<VReg>(use)) {
              if (auto it = regMap.find(vreg); it != regMap.end()) {
                use = it->second;
              } else if (regAlloc.spills.count(vreg)) {
                // load it with ldr lr
                use = PReg::lr();
                int offset = spillMap.at(vreg);
                auto loadSlotInst = new AsmLoadInst{};
                generateSpillAddress(loadSlotInst, offset);
                loadSlotInst->dst = use;
                label->push_before(inst, loadSlotInst);
              }
            }
          }
        }
      }
    }
  }

  void run() {
    runRegAlloc();
    
    os << ".arch armv7ve\n";
    os << ".text\n";
    for (auto *func : module->funcs) {
      os << ".global " << func->name << "\n";
    }

    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;
      os << func->name << ":\n";
      curFunc = func;

      // function prologue
      printArmInstr("push", {"{lr}"});

      assert(curFunc->stackSize < 4096 && "Stack size too large");
      printArmInstr(
          "sub", {"sp", "sp", "#" + std::to_string(curFunc->stackSize)});

      for (auto *label : func->labels) {
        os << getLabel(label) << ":\n";
        for (auto *inst = label->Head; inst; inst = inst->Next) {
          if (auto *retInst = dyn_cast<AsmReturnInst>(inst)) {
            printArmInstr(
                "add", {"sp", "sp", "#" + std::to_string(curFunc->stackSize)});

            printArmInstr("pop", {"{lr}"});
            printArmInstr("bx", {"lr"});
            // TODO: constant pool ltorg?
          } else if (auto *movInst = dyn_cast<AsmMoveInst>(inst)) {
            auto reg_dst = cast<PReg>(movInst->dst);
            if (auto *imm = dyn_cast<AsmImm>(movInst->src)) {
              union {
                uint32_t i;
                struct {
                  uint16_t lo;
                  uint16_t hi;
                };
              } u;
              u.i = imm->hexValue;
              printArmInstr("movw", {reg_dst->abiName(), std::to_string(u.lo)});
              if (u.hi > 0)
                printArmInstr(
                    "movt", {reg_dst->abiName(), std::to_string(u.hi)});
            } else if (auto *reg = dyn_cast<PReg>(movInst->src)) {
              printArmInstr("mov", {reg_dst->abiName(), reg->abiName()});
            } else {
              olc_unreachable("NYI");
            }
          } else if (auto *binInst = dyn_cast<AsmBinaryInst>(inst)) {
            std::string op;
            switch (binInst->tag) {
            case AsmInst::Tag::Add:
              op = "add";
              break;
            case AsmInst::Tag::Sub:
              op = "sub";
              break;
            case AsmInst::Tag::Mul:
              op = "mul";
              break;
            case AsmInst::Tag::Div:
              // op = "sdiv";
              // if (cast<PReg>(binInst->dst)->type == AsmType::F32) {
              //   op = "vdiv.f32";
              // }
              if (cast<PReg>(binInst->dst)->type == AsmType::F32) {
                op = "vdiv.f32";
              } else {
                op = "sdiv";
              }
              break;
            case AsmInst::Tag::Mod:
              olc_unreachable("Should not produce MOD in IR");
            default:
              olc_unreachable("Unknown");
            }
            auto reg_dst = cast<PReg>(binInst->dst);
            auto reg_lhs = cast<PReg>(binInst->lhs);
            if (auto reg_rhs = dyn_cast<PReg>(binInst->rhs)) {
              // os << op << "\t" << x->dst << ", " << x->lhs << ", " << x->rhs;
              printArmInstr(
                  op,
                  {reg_dst->abiName(), reg_lhs->abiName(), reg_rhs->abiName()});
            } else {
              auto imm = cast<AsmImm>(binInst->rhs);
              assert(imm->hexValue < 4096 && "imm12bit, large imm NYI");
              printArmInstr(
                  op, {reg_dst->abiName(), reg_lhs->abiName(),
                       "#" + std::to_string(imm->hexValue)});
            }
          } else if (auto *ldInst = dyn_cast<AsmLoadInst>(inst)) {
            auto reg_dst = cast<PReg>(ldInst->dst);
            auto reg_base = cast<PReg>(ldInst->addr);
            if (ldInst->offset) {
              printArmInstr(
                  "ldr", {reg_dst->abiName(),
                          "[" + reg_base->abiName() + ", " +
                              cast<AsmImm>(ldInst->offset)->toAsm() + "]"});
            } else {
              printArmInstr(
                  "ldr", {reg_dst->abiName(), "[" + reg_base->abiName() + "]"});
            }
          } else if (auto *stInst = dyn_cast<AsmStoreInst>(inst)) {
            auto reg_src = cast<PReg>(stInst->src);
            auto reg_base = cast<PReg>(stInst->addr);
            if (stInst->offset) {
              printArmInstr(
                  "str", {reg_src->abiName(),
                          "[" + reg_base->abiName() + ", " +
                              cast<AsmImm>(stInst->offset)->toAsm() + "]"});
            } else {
              printArmInstr(
                  "str", {reg_src->abiName(), "[" + reg_base->abiName() + "]"});
            }
          } else if (auto *callInst = dyn_cast<AsmCallInst>(inst)) {
            printArmInstr("bl", {callInst->callee});
          } else if (auto *brInst = dyn_cast<AsmBranchInst>(inst)) {
            if (brInst->pred != AsmPredicate::Al) {
              // 处理条件分支
              std::string condTag = getCondStr(brInst->pred);
              printArmInstr("b" + condTag, {getLabel(brInst->trueTarget)});
              printArmInstr("b", {getLabel(brInst->falseTarget)});
            } else {
              // 处理无条件跳转
              printArmInstr("b", {getLabel(brInst->trueTarget)});
            }
          } else if (auto *cmpInst = dyn_cast<AsmCompareInst>(inst)) {
            // 处理比较指令
            auto reg_lhs = cast<PReg>(cmpInst->lhs);
            auto reg_rhs = cast<PReg>(cmpInst->rhs);
            printArmInstr("cmp", {reg_lhs->abiName(), reg_rhs->abiName()});
          } else if (auto *jmpInst = dyn_cast<AsmJumpInst>(inst)) {
            // 处理无条件跳转指令
            printArmInstr("b", {getLabel(jmpInst->target)});
          } else {
            olc_unreachable("NYI");
          }
        }
      }
    }
  }
};

} // namespace olc
