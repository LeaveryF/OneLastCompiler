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

  struct CallInfo {
    std::vector<Value *> argsInIntReg, argsInFloatReg;
    std::vector<Value *> argsOnStack;
  };

  template <typename T>
  auto arrangeCallInfo(std::vector<T> const &args) -> CallInfo {
    CallInfo info{};
    constexpr size_t maxIntRegs = 4, maxFloatRegs = 16;
    for (auto const &rarg : args) {
      auto arg = cast<Value>(rarg);
      if (arg->getType()->isIntegerTy() && info.argsInFloatReg.size() < 4) {
        info.argsInFloatReg.push_back(arg);
      } else if (arg->getType()->isFloatTy() && info.argsInIntReg.size() < 16) {
        info.argsInIntReg.push_back(arg);
      } else {
        info.argsOnStack.push_back(arg);
      }
    }
    return info;
  }

  void run() {
    for (auto *irFunc : irModule->functions) {
      auto asmFunc = new AsmFunc{irFunc->fnName};
      asmFunc->isBuiltin = irFunc->isBuiltin;
      fnMap[irFunc] = asmFunc;
      asmModule->funcs.push_back(asmFunc);
      auto args = irFunc->args;

      auto &&[argsInIntReg, argsInFloatReg, argsOnStack] =
          arrangeCallInfo(args);
      // 声明参数的寄存器 r0-r3 / s0-s15
      for (unsigned i = 0; i < argsInIntReg.size(); i++) {
        valueMap[argsInIntReg[i]] = AsmReg::makePReg(AsmType::I32, i);
      }
      for (unsigned i = 0; i < argsInFloatReg.size(); i++) {
        valueMap[argsInFloatReg[i]] = AsmReg::makePReg(AsmType::F32, i);
      }
      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = new AsmLabel{irBB->label};
        labelMap[irBB] = asmLabel;
        asmFunc->labels.push_back(asmLabel);
        if (irBB == irFunc->basicBlocks.front()) {
          // 声明参数的栈空间 ldr value, [sp, #(n-i)*4], i = 0..n-1
          int argsOffset = argsOnStack.size() * 4;
          for (const auto &argOnStack : argsOnStack) {
            // add rx, sp, (n-i)*4 随后将虚拟寄存器交给alloca处理 不需要ldr
            auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Add};
            spOffsetInst->lhs = AsmReg::sp();
            spOffsetInst->rhs = lowerImm(argsOffset);
            spOffsetInst->dst =
                AsmReg::makeVReg(convertType(argOnStack->getType()));
            asmLabel->push_back(spOffsetInst);
            valueMap[argOnStack] =
                AsmReg::makeVReg(convertType(argOnStack->getType()));
          }
        }
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

            auto &&[argsInIntRegs, argsInFloatRegs, argsOnStack] =
                arrangeCallInfo(args);
            // 寄存器传参 r0-r3 / s0-s15  mov ri, value
            for (unsigned i = 0; i < argsInIntRegs.size(); i++) {
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(args[i], asmLabel);
              asmMovInst->dst = AsmReg::makePReg(AsmType::I32, i);
              asmLabel->push_back(asmMovInst);
            }
            for (unsigned i = 0; i < argsInFloatRegs.size(); i++) {
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(args[i], asmLabel);
              asmMovInst->dst = AsmReg::makePReg(AsmType::F32, i);
              asmLabel->push_back(asmMovInst);
            }
            // 栈传参 str value, [sp, #-(stacksize+i*4)]
            int argsOffset = 0;
            for (const auto &argOnStack : argsOnStack) {
              // sub rx, sp, i*4
              auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Sub};
              spOffsetInst->lhs = AsmReg::sp();
              spOffsetInst->rhs = lowerImm(asmFunc->stackSize + argsOffset);
              spOffsetInst->dst =
                  AsmReg::makeVReg(convertType(argOnStack->getType()));
              asmLabel->push_back(spOffsetInst);
              // str value, [rx]
              auto *asmStoreInst = new AsmStoreInst{};
              asmStoreInst->addr = spOffsetInst->dst;
              asmStoreInst->src = lowerValueToReg(argOnStack, asmLabel);
              asmLabel->push_back(asmStoreInst);
              argsOffset += 4;
            }
            // sub sp, sp, (n-4)*4
            auto *subInst = new AsmBinaryInst{AsmInst::Tag::Sub};
            subInst->lhs = AsmReg::sp();
            subInst->rhs = lowerImm(argsOffset);
            subInst->dst = AsmReg::sp();
            asmLabel->push_back(subInst);
            // bl func
            auto *asmCallInst =
                new AsmCallInst{irCallInst->getCallee()->fnName};
            asmLabel->push_back(asmCallInst);
            // add sp, sp, (n-4)*4
            auto *addInst = new AsmBinaryInst{AsmInst::Tag::Add};
            addInst->lhs = AsmReg::sp();
            addInst->rhs = lowerImm(argsOffset);
            addInst->dst = AsmReg::sp();
            // 返回值 mov value, r0 / s0
            if (!irCallInst->getType()->isVoidTy()) {
              valueMap[irCallInst] =
                  AsmReg::makePReg(convertType(irCallInst->getType()), 0);
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src =
                  AsmReg::makePReg(convertType(irCallInst->getType()), 0);
              asmMovInst->dst = lowerValue(irCallInst, asmLabel);
              asmLabel->push_back(asmMovInst);
            }
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
