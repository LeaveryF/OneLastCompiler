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

  void runRegAlloc() {
    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;
      LinearScan regAlloc;
      regAlloc.runOnFunction(func);
      auto &regMap = regAlloc.regMap;
      for (auto *label : func->labels) {
        for (auto *inst = label->Head; inst != nullptr; inst = inst->Next) {
          for (auto refdef : inst->getDefs()) {
            auto &def = *refdef;
            assert(isa<AsmReg>(def) && "Non-reg def!");
            if (auto *preg = dyn_cast<PReg>(def)) {
              continue;
            } else if (auto *vreg = dyn_cast<VReg>(def)) {
              assert(regMap.count(vreg) && "Spill detected, NYI");
              def = regMap.at(vreg);
            } else {
              olc_unreachable("Invalid asm reg for def");
            }
          }

          for (auto refuse : inst->getUses()) {
            auto &use = *refuse;
            if (auto *vreg = dyn_cast_if_present<VReg>(use)) {
              if (regMap.find(vreg) == regMap.end()) {
                olc_unreachable("Spill detected, NYI");
              }
              use = regMap.at(vreg);
            }
          }
        }
      }
    }
  }

  void run() {
    runRegAlloc();

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
        // TODO: label name uniquer
        os << "." << label->name << ":\n";
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
              op = "idiv";
              if (cast<PReg>(binInst->dst)->type == AsmType::F32) {
                op = "vdiv";
              }
              break;
            case AsmInst::Tag::Mod:
              op = "mod";
              break;
            default:
              olc_unreachable("Unknown");
            }
            auto reg_dst = cast<PReg>(binInst->dst);
            auto reg_lhs = cast<PReg>(binInst->lhs);
            if (op == "idiv") {
              // 整数除法
              printArmInstr("bl", {"__aeabi_idiv"});
              printArmInstr("mov", {reg_dst->abiName(), "r0"});
            } else if (op == "vdiv") {
              // 浮点数除法
              printArmInstr(
                  "vdiv.f32", {reg_dst->abiName(), reg_lhs->abiName(),
                               cast<PReg>(binInst->rhs)->abiName()});
            } else if (op == "mod") {
              // 整数取模
              printArmInstr("bl", {"__aeabi_idivmod"});
              printArmInstr("mov", {reg_dst->abiName(), "r1"});
            } else if (auto reg_rhs = dyn_cast<PReg>(binInst->rhs)) {
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
            assert(!ldInst->offset && "offset NYI");
            printArmInstr(
                "ldr", {reg_dst->abiName(), "[" + reg_base->abiName() + "]"});
          } else if (auto *stInst = dyn_cast<AsmStoreInst>(inst)) {
            auto reg_src = cast<PReg>(stInst->src);
            auto reg_base = cast<PReg>(stInst->addr);
            assert(!stInst->offset && "offset NYI");
            printArmInstr(
                "str", {reg_src->abiName(), "[" + reg_base->abiName() + "]"});
          } else if (auto *callInst = dyn_cast<AsmCallInst>(inst)) {
            printArmInstr("bl", {callInst->callee});
          } else if (auto *brInst = dyn_cast<AsmBranchInst>(inst)) {
            if (brInst->pred != AsmPredicate::Al) {
              // 处理条件分支
              std::string condTag = getCondStr(brInst->pred);
              printArmInstr("b" + condTag, {"." + brInst->trueTarget->name});
              printArmInstr("b", {"." + brInst->falseTarget->name});
            } else {
              // 处理无条件跳转
              printArmInstr("b", {"." + brInst->trueTarget->name});
            }
          } else if (auto *cmpInst = dyn_cast<AsmCompareInst>(inst)) {
            // 处理比较指令
            auto reg_lhs = cast<PReg>(cmpInst->lhs);
            auto reg_rhs = cast<PReg>(cmpInst->rhs);
            printArmInstr("cmp", {reg_lhs->abiName(), reg_rhs->abiName()});
          } else if (auto *jmpInst = dyn_cast<AsmJumpInst>(inst)) {
            // 处理无条件跳转指令
            printArmInstr("b", {"." + jmpInst->target->name});
          }
          else {
            olc_unreachable("NYI");
          }
        }
      }
    }
  }
};

} // namespace olc
