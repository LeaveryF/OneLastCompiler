#pragma once

#include <olc/Support.h>

#include <olc/backend/MachineIR.h>
#include <olc/ir/IR.h>

#include <map>

namespace olc {

struct CodeGen {

  Module *irModule = nullptr;
  AsmModule *asmModule = nullptr;
  std::map<Value *, AsmValue *> valueMap;
  std::map<Function *, AsmFunc *> fnMap;
  std::map<BasicBlock *, AsmLabel *> labelMap;

  CodeGen(Module *module) : irModule(module), asmModule(new AsmModule{}) {}

  AsmPredicate getAsmPred(Value::Tag tag) {
    switch (tag) {
    case Value::Tag::Lt:
      return AsmPredicate::Lt;
    case Value::Tag::Le:
      return AsmPredicate::Le;
    case Value::Tag::Gt:
      return AsmPredicate::Gt;
    case Value::Tag::Ge:
      return AsmPredicate::Ge;
    case Value::Tag::Eq:
      return AsmPredicate::Eq;
    case Value::Tag::Ne:
      return AsmPredicate::Ne;
    default:
      olc_unreachable("invalid tag");
    }
  }

  AsmType convertType(Type *type) {
    if (type->isFloatTy()) {
      return AsmType::F32;
    } else {
      return AsmType::I32;
    }
  }

  AsmBinaryInst::Tag convertBinOpTag(BinaryInst::Tag tag) {
    switch (tag) {
    case BinaryInst::Tag::Add:
      return AsmBinaryInst::Tag::Add;
    case BinaryInst::Tag::Sub:
      return AsmBinaryInst::Tag::Sub;
    case BinaryInst::Tag::Mul:
      return AsmBinaryInst::Tag::Mul;
    case BinaryInst::Tag::Div:
      return AsmBinaryInst::Tag::Div;
    case BinaryInst::Tag::Mod:
      return AsmBinaryInst::Tag::Mod;
    case BinaryInst::Tag::Lt:
    case BinaryInst::Tag::Le:
    case BinaryInst::Tag::Gt:
    case BinaryInst::Tag::Ge:
    case BinaryInst::Tag::Eq:
    case BinaryInst::Tag::Ne:
      return AsmBinaryInst::Tag::Cmp;
    default:
      olc_unreachable("invalid tag");
    }
  }

  AsmImm *lowerImm(int value) {
    return new AsmImm{static_cast<uint32_t>(value)};
  }

  AsmValue *lowerValue(Value *value, AsmLabel *label) {
    if (auto *irConst = dyn_cast<ConstantValue>(value)) {
      if (irConst->isInt()) {
        return lowerImm(irConst->getInt());
      } else {
        olc_unreachable("float NYI");
      }
    } else if (auto *irGlobal = dyn_cast<GlobalVariable>(value)) {
      // label->create<LoadGlobalAddr>
      olc_unreachable("global NYI");
    } else {
      return valueMap.at(value);
    }
  }

  AsmReg *lowerValueToReg(Value *value, AsmLabel *label) {
    auto *asmValue = lowerValue(value, label);
    if (auto *asmReg = dyn_cast<AsmReg>(asmValue)) {
      return asmReg;
    } else {
      asmReg = AsmReg::makeVReg(convertType(value->getType()));
      auto *asmMovInst = new AsmMoveInst{};
      asmMovInst->src = asmValue;
      asmMovInst->dst = asmReg;
      label->push_back(asmMovInst);
      return asmReg;
    }
  }

  void run() {
    for (auto *irFunc : irModule->functions) {
      auto asmFunc = new AsmFunc{irFunc->fnName};
      asmFunc->isBuiltin = irFunc->isBuiltin;
      fnMap[irFunc] = asmFunc;
      asmModule->funcs.push_back(asmFunc);
      auto args = irFunc->args;
      for (int i = 0; i < args.size(); ++i) {
        if (i < 4) {
          // 声明参数的寄存器 r0-r3
          auto *res_reg = AsmReg::makePReg(convertType(args[i]->getType()), i);
          valueMap[args[i]] = res_reg;
        } else {
          // 声明参数的栈空间
          olc_unreachable("NYI");
        }
      }
      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = new AsmLabel{irBB->label};
        labelMap[irBB] = asmLabel;
        asmFunc->labels.push_back(asmLabel);
        for (auto *irInst : irBB->instructions) {
          if (auto *irRetInst = dyn_cast<ReturnInst>(irInst)) {
            if (auto *retVal = irRetInst->getReturnValue()) {
              // mov r0 / s0, value
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(retVal, asmLabel);
              asmMovInst->dst =
                  AsmReg::makePReg(convertType(retVal->getType()), 0);
              asmLabel->push_back(asmMovInst);
            }
            asmLabel->push_back(new AsmReturnInst);
          } else if (auto *irBinInst = dyn_cast<BinaryInst>(irInst)) {
            auto reg_res = AsmReg::makeVReg(convertType(irBinInst->getType()));
            auto *asmBinInst =
                new AsmBinaryInst{convertBinOpTag(irBinInst->tag)};
            // TODO: optimize with immediates
            asmBinInst->lhs = lowerValueToReg(irBinInst->getLHS(), asmLabel);
            asmBinInst->rhs = lowerValueToReg(irBinInst->getRHS(), asmLabel);
            asmBinInst->dst = reg_res;
            valueMap[irBinInst] = reg_res;
            asmLabel->push_back(asmBinInst);
          } else if (auto *irAllocaInst = dyn_cast<AllocaInst>(irInst)) {
            auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Add};
            spOffsetInst->lhs = AsmReg::sp();
            spOffsetInst->rhs = lowerImm(asmFunc->stackSize);
            spOffsetInst->dst = AsmReg::makeVReg(AsmType::I32);
            valueMap[irAllocaInst] = spOffsetInst->dst;
            asmFunc->stackSize += irAllocaInst->getAllocatedSize();
            asmLabel->push_back(spOffsetInst);
          } else if (auto *irLoadInst = dyn_cast<LoadInst>(irInst)) {
            auto reg_res = AsmReg::makeVReg(convertType(irLoadInst->getType()));
            auto *asmLoadInst = new AsmLoadInst{};
            asmLoadInst->addr = lowerValue(irLoadInst->getPointer(), asmLabel);
            asmLoadInst->dst = reg_res;
            valueMap[irLoadInst] = reg_res;
            asmLabel->push_back(asmLoadInst);
          } else if (auto *irStoreInst = dyn_cast<StoreInst>(irInst)) {
            auto reg_src = lowerValueToReg(irStoreInst->getValue(), asmLabel);
            auto *asmStoreInst = new AsmStoreInst{};
            asmStoreInst->addr =
                lowerValue(irStoreInst->getPointer(), asmLabel);
            asmStoreInst->src = reg_src;
            asmLabel->push_back(asmStoreInst);
          } else if (auto *irCallInst = dyn_cast<CallInst>(irInst)) {
            auto args = irCallInst->getArgs();
            // 参数 r0-r3 / s0-s15
            for (int i = 0; i < args.size(); ++i) {
              if (i < 4) {
                // 寄存器传参
                auto *asmMovInst = new AsmMoveInst{};
                asmMovInst->src = lowerValue(args[i], asmLabel);
                asmMovInst->dst =
                    AsmReg::makePReg(convertType(args[i]->getType()), i);
                asmLabel->push_back(asmMovInst);
              } else {
                // 栈传参
                olc_unreachable("NYI");
              }
              // bl fname
              auto *asmCallInst =
                  new AsmCallInst{irCallInst->getCallee()->fnName};
              asmLabel->push_back(asmCallInst);
              // 返回值
              if (!irCallInst->getType()->isVoidTy()) {
                // mov value, r0 / s0
                valueMap[irCallInst] =
                    AsmReg::makePReg(convertType(irCallInst->getType()), 0);
                auto *asmMovInst = new AsmMoveInst{};
                asmMovInst->src =
                    AsmReg::makePReg(convertType(irCallInst->getType()), 0);
                asmMovInst->dst = lowerValue(irCallInst, asmLabel);
                asmLabel->push_back(asmMovInst);
              }
            }
          } else if (auto *irBranchInst = dyn_cast<BranchInst>(irInst)) {
            // 处理分支指令
            auto *branchInst = new AsmBranchInst{};
            auto *cond = dyn_cast<BinaryInst>(irBranchInst->getCondition());
            branchInst->pred = getAsmPred(cond->tag);
            branchInst->trueTarget = new AsmLabel{irBranchInst->getTrueBlock()->label};
            branchInst->falseTarget = new AsmLabel{irBranchInst->getFalseBlock()->label};
            asmLabel->push_back(branchInst);
          } else if (auto *irJumpInst = dyn_cast<JumpInst>(irInst)) {
            // 处理无条件跳转指令
            auto *jumpInst = new AsmJumpInst{nullptr};
            jumpInst->target = new AsmLabel{irJumpInst->getTargetBlock()->label};
            asmLabel->push_back(jumpInst);
          } else {
            olc_unreachable("NYI");
          }
        }
      }

      // Copy preds and succs from IR
      for (auto *irBB : irFunc->basicBlocks) {
        auto *asmLabel = labelMap.at(irBB);
        for (auto *irSucc : irBB->successors)
          asmLabel->succs.push_back(labelMap.at(irSucc));

        for (auto *irPred : irBB->predecessors)
          asmLabel->preds.push_back(labelMap.at(irPred));
      }
    }
  }
};

} // namespace olc
