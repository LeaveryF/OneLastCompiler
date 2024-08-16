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

  // When exceeding 1000, split the label and insert ltorg.
  size_t labelInstCounter = 0;
  // Generate a unique name for the new split label.
  size_t labelSplitCounter = 0;
  static constexpr size_t kMaxInstInLabel = 1000;

  std::unordered_map<std::string, std::string> i2fOpCode{
      {"add", "vadd.f32"},  {"sub", "vsub.f32"}, {"mul", "vmul.f32"},
      {"sdiv", "vdiv.f32"}, {"cmp", "vcmp.f32"}, {"mov", "vmov.f32"},
      {"ldr", "vldr.32"},   {"str", "vstr.32"},
  };

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

    if (++labelInstCounter > kMaxInstInLabel) {
      labelInstCounter = 0;
      auto name = "split_label_" + std::to_string(labelSplitCounter++);
      os << "  b " << name << "\n";
      os << ".ltorg\n";
      os << name << ":\n";
    }
  }

  enum class RegSaveType {
    Push,
    Pop,
  };

  void printStackMovement(RegSaveType type, AsmFunc *func) {
    int size = func->stackSize;
    std::string op = type == RegSaveType::Push ? "sub" : "add";
    if (AsmImm::match<AsmImm::Operand2>(size)) {
      printArmInstr(op, {"sp", "sp", "#" + std::to_string(size)});
    } else {
      // use lr as temp reg, which is covered by reg save store
      printArmInstr("ldr", {"lr", "=" + std::to_string(size)});
      printArmInstr(op, {"sp", "lr"});
    }
  }

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
          // We only have 1 temp reg: lr. If > 1 def or use is spilled for an
          // instruction, we cannot handle it.
          int cntSpillDef = 0, cntSpillUse = 0;
          for (auto refdef : inst->getDefs()) {
            auto &def = *refdef;
            assert(isa<AsmReg>(def) && "Non-reg def!");
            if (auto *preg = dyn_cast<PReg>(def)) {
              continue;
            } else if (auto *vreg = dyn_cast<VReg>(def)) {
              if (auto it = regMap.find(vreg); it != regMap.end()) {
                def = it->second;
              } else if (regAlloc.spills.count(vreg)) {
                assert(cntSpillDef < 1 && "Too many spills in an inst");
                cntSpillDef++;
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
                assert(cntSpillUse < 1 && "Too many spills in an inst");
                cntSpillUse++;
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

  void peepHole() {
    for (auto *func : module->funcs) {
      if (func->isBuiltin)
        continue;
      for (auto *label : func->labels) {
        for (auto *inst = label->Head; inst; inst = inst->Next) {
          if (auto *movInst = dyn_cast<AsmMoveInst>(inst)) {
            if (movInst->src == movInst->dst) {
              label->remove(movInst);
            }
          } else if (auto *ldInst = dyn_cast<AsmLoadInst>(inst)) {
            if (inst->Prev) {
              if (auto *stInst = dyn_cast<AsmStoreInst>(inst->Prev)) {
                if (stInst->src == ldInst->dst &&
                    stInst->addr == ldInst->addr) {
                  label->remove(ldInst);
                }
              }
            }
          } else if (auto *stInst = dyn_cast<AsmStoreInst>(inst)) {
            if (inst->Prev) {
              if (auto *ldInst = dyn_cast<AsmLoadInst>(inst->Prev)) {
                if (ldInst->dst == stInst->src &&
                    ldInst->addr == stInst->addr) {
                  label->remove(stInst);
                }
              }
            }
          } else {
            // pass
          }
        }
      }
    }
  }

  void run() {
    runRegAlloc();
    calcStackInfo();
    peepHole();

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
      printStackMovement(RegSaveType::Push, func);

      for (auto *label : func->labels) {
        labelInstCounter = 0;
        os << getLabel(label) << ":\n";
        for (auto *inst = label->Head; inst; inst = inst->Next) {
          if (auto *retInst = dyn_cast<AsmReturnInst>(inst)) {
            printStackMovement(RegSaveType::Pop, func);
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
              std::string op;
              if (reg_dst->type == AsmType::F32) {
                op = "vmov.f32";
              } else {
                op = "mov";
              }
              printArmInstr(
                  op, {reg_dst->abiName(), reg->abiName()}, movInst->pred);
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
              // if (cast<PReg>(binInst->dst)->type == AsmType::F32) {
              //   op = "vdiv.f32";
              // } else {
              //   op = "sdiv";
              // }
              op = "sdiv";
              break;
            case AsmInst::Tag::Mod:
              olc_unreachable("Should not produce MOD in IR");
            default:
              olc_unreachable("Unknown");
            }
            if (cast<PReg>(binInst->dst)->type == AsmType::F32) {
              op = i2fOpCode[op];
            }
            auto reg_dst = cast<PReg>(binInst->dst);
            auto reg_lhs = cast<PReg>(binInst->lhs);
            std::vector<std::string> operands;
            if (auto reg_rhs = dyn_cast<PReg>(binInst->rhs)) {
              operands = {
                  reg_dst->abiName(), reg_lhs->abiName(), reg_rhs->abiName()};
            } else {
              auto imm = cast<AsmImm>(binInst->rhs);
              operands = {reg_dst->abiName(), reg_lhs->abiName(), imm->toAsm()};
            }
            if (binInst->shift != 0) {
              assert(binInst->shift > 0 && "Only LSL is supported");
              operands.push_back("lsl #" + std::to_string(binInst->shift));
            }
            printArmInstr(op, operands);
          } else if (auto *ldInst = dyn_cast<AsmLoadInst>(inst)) {
            auto reg_dst = cast<PReg>(ldInst->dst);
            auto reg_base = cast<PReg>(ldInst->addr);
            std::string op;
            if (reg_dst->type == AsmType::F32) {
              op = "vldr.32";
            } else {
              op = "ldr";
            }
            if (ldInst->offset) {
              printArmInstr(
                  op, {reg_dst->abiName(),
                       "[" + reg_base->abiName() + ", " +
                           cast<AsmImm>(ldInst->offset)->toAsm() + "]"});
            } else {
              printArmInstr(
                  op, {reg_dst->abiName(), "[" + reg_base->abiName() + "]"});
            }
          } else if (auto *stInst = dyn_cast<AsmStoreInst>(inst)) {
            auto reg_src = cast<PReg>(stInst->src);
            auto reg_base = cast<PReg>(stInst->addr);
            std::string op;
            if (reg_src->type == AsmType::F32) {
              op = "vstr.32";
            } else {
              op = "str";
            }
            if (stInst->offset) {
              printArmInstr(
                  op, {reg_src->abiName(),
                       "[" + reg_base->abiName() + ", " +
                           cast<AsmImm>(stInst->offset)->toAsm() + "]"});
            } else {
              printArmInstr(
                  op, {reg_src->abiName(), "[" + reg_base->abiName() + "]"});
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
            std::string op;
            if (reg_lhs->type == AsmType::F32) {
              op = "vcmp.f32";
            } else {
              op = "cmp";
            }
            if (auto reg_rhs = dyn_cast<PReg>(cmpInst->rhs))
              printArmInstr("cmp", {reg_lhs->abiName(), reg_rhs->abiName()});
            else if (auto *imm_rhs = dyn_cast<AsmImm>(cmpInst->rhs)) {
              printArmInstr("cmp", {reg_lhs->abiName(), imm_rhs->toAsm()});
            } else {
              olc_unreachable("NYI");
            }

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
