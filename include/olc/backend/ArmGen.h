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

  uint32_t reinterpretFloat(float x) {
    union {
      float f;
      uint32_t i;
    } u;
    u.f = x;
    return u.i;
  }

  void printArmInstr(
      const std::string &op, const std::vector<std::string> &operands = {},
      AsmPredicate pred = AsmPredicate::Al) {

    // indent for instructions
    os << "  ";

    os << op;
    if (pred != AsmPredicate::Al) {
      os << getCondStr(pred);
    }
    os << " ";
    for (int i = 0; i < operands.size(); ++i) {
      if (i > 0) {
        os << ", ";
      }
      os << operands[i];
    }
    os << '\n';
  }

  enum class RegSaveType {
    Push,
    Pop,
  };

  /// Print push or pop { ...calleeSavedRegs, lr }
  void printRegSaveStore(RegSaveType type, AsmFunc *func) {
    std::string regs;
    for (auto *reg : func->usedCalleeSavedRegs) {
      if (!regs.empty())
        regs += ", ";
      regs += reg->abiName();
    }
    // always save lr
    if (!regs.empty())
      regs += ", ";
    regs += PReg::lr()->abiName();
    printArmInstr(
        type == RegSaveType::Push ? "push" : "pop", {"{" + regs + "}"});
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
              } else {
                // unused dst
                def = PReg::lr();
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

  void calcStackInfo() {
    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;

      // 1. scan used callee saved regs list

      auto processReg = [&](AsmValue *reg) {
        auto *preg = dyn_cast_if_present<PReg>(reg);
        if (!preg)
          return;
        if (preg->id >= 4 && preg->id <= 11) {
          func->usedCalleeSavedRegs.insert(preg);
        }
      };

      for (auto *label : func->labels) {
        for (auto *inst = label->Head; inst; inst = inst->Next) {
          for (auto *refdef : inst->getDefs())
            processReg(*refdef);
          for (auto *refuse : inst->getUses())
            processReg(*refuse);
        }
      }

      // 2. replace stack arg offsets
      const int pushSize = 4 + 4 * func->usedCalleeSavedRegs.size();
      if ((func->stackSize + pushSize) % 8 != 0) {
        func->stackSize += 4;
      }

      for (auto *offsetInst : func->stackArgOffsets) {
        auto *offsetImm = cast<AsmImm>(offsetInst->rhs);
        offsetImm->hexValue += func->stackSize + pushSize;
      }
    }
  }

  void printGlobalData(GlobalVariable *global) {
    if (!global->getInitializer())
      return;

    os << global->getName() << ":\n";
    std::function<void(Constant *)> printConstData = [&](Constant *val) {
      assert(val && "Invalid initializer");
      if (auto *arr = dyn_cast<ConstantArray>(val)) {
        for (auto *elt : arr->values) {
          printConstData(elt);
        }
        size_t totalCount = cast<ArrayType>(arr->getType())->getSize();
        // 不足的部分自动填充0
        if (totalCount > arr->values.size()) {
          os << ".zero " << 4 * (totalCount - arr->values.size()) << '\n';
        }
        os << ".size " << global->getName() << ", " << totalCount * 4 << '\n';
      } else if (auto *constVal = dyn_cast<ConstantValue>(val)) {
        if (constVal->isInt()) {
          os << ".word " << constVal->getInt() << '\n';
        } else {
          os << ".word " << reinterpretFloat(constVal->getFloat()) << '\n';
        }
      } else {
        olc_unreachable("NYI");
      }
    };
    printConstData(global->getInitializer());
  }

  void printGlobalBss(GlobalVariable *global) {
    if (global->getInitializer()) {
      return;
    }
    os << global->getName() << ":\n";
    unsigned size = 4;
    if (auto *arrTy = dyn_cast<ArrayType>(global->getAllocatedType())) {
      assert(!arrTy->getArrayEltType()->isArrayTy() && "invalid");
      size = 4 * arrTy->getSize();
    }
    os << ".skip " << size << '\n';
  }

  void run() {
    runRegAlloc();
    calcStackInfo();

    os << ".arch armv7ve\n";

    os << ".data\n";
    for (auto &global : module->globals) {
      printGlobalData(global);
    }

    os << ".bss\n";
    for (auto &global : module->globals) {
      printGlobalBss(global);
    }

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
      printRegSaveStore(RegSaveType::Push, func);

      assert(curFunc->stackSize < 4096 && "Stack size too large");
      printArmInstr(
          "sub", {"sp", "sp", "#" + std::to_string(curFunc->stackSize)});

      for (auto *label : func->labels) {
        os << getLabel(label) << ":\n";
        for (auto *inst = label->Head; inst; inst = inst->Next) {
          if (auto *retInst = dyn_cast<AsmReturnInst>(inst)) {
            printArmInstr(
                "add", {"sp", "sp", "#" + std::to_string(curFunc->stackSize)});

            printRegSaveStore(RegSaveType::Pop, func);
            printArmInstr("bx", {"lr"});
            printArmInstr(".ltorg");
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
              printArmInstr(
                  "movw", {reg_dst->abiName(), std::to_string(u.lo)},
                  movInst->pred);
              if (u.hi > 0)
                printArmInstr(
                    "movt", {reg_dst->abiName(), std::to_string(u.hi)},
                    movInst->pred);
            } else if (auto *reg = dyn_cast<PReg>(movInst->src)) {
              printArmInstr(
                  "mov", {reg_dst->abiName(), reg->abiName()}, movInst->pred);
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
            std::vector<std::string> operands;
            if (auto reg_rhs = dyn_cast<PReg>(binInst->rhs)) {
              operands = {
                  reg_dst->abiName(), reg_lhs->abiName(), reg_rhs->abiName()};
            } else {
              auto imm = cast<AsmImm>(binInst->rhs);
              assert(imm->hexValue < 4096 && "imm12bit, large imm NYI");
              operands = {
                  reg_dst->abiName(), reg_lhs->abiName(),
                  "#" + std::to_string(imm->hexValue)};
            }
            if (binInst->shift != 0) {
              assert(binInst->shift > 0 && "Only LSL is supported");
              operands.push_back("lsl #" + std::to_string(binInst->shift));
            }
            printArmInstr(op, operands);
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
            printArmInstr(".ltorg");
          } else if (auto *ldGlbInst = dyn_cast<AsmLoadGlobalInst>(inst)) {
            // 处理全局变量加载指令
            auto reg_dst = cast<PReg>(ldGlbInst->dst);
            printArmInstr(
                "ldr", {reg_dst->abiName(), "=" + ldGlbInst->var->getName()});
          } else {
            olc_unreachable("NYI");
          }
        }
      }
    }
  }
};

} // namespace olc
