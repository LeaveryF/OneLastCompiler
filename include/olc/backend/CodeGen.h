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

  AsmValue *lowerValue(Value *value) {
    if (auto *irConst = dyn_cast<ConstantValue>(value)) {
      if (irConst->isInt()) {
        return new AsmImm{static_cast<uint32_t>(irConst->getInt())};
      } else {
        olc_unreachable("NYI");
      }
    } else {
      return valueMap.at(value);
    }
  }

  void run() {
    for (auto *irFunc : irModule->functions) {
      auto asmFunc = new AsmFunc{irFunc->fnName};
      asmFunc->isBuiltin = irFunc->isBuiltin;
      fnMap[irFunc] = asmFunc;
      asmModule->funcs.push_back(asmFunc);
      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = new AsmLabel{irBB->label};
        labelMap[irBB] = asmLabel;
        asmFunc->labels.push_back(asmLabel);
        for (auto *irInst : irBB->instructions) {
          if (auto *irRetInst = dyn_cast<ReturnInst>(irInst)) {
            if (auto *retVal = irRetInst->getReturnValue()) {
              // mov r0 / s0, value
              auto *asmMovInst = asmLabel->create<AsmMoveInst>();
              asmMovInst->src = lowerValue(retVal);
              asmMovInst->dst =
                  AsmReg::makePReg(convertType(retVal->getType()), 0);
            }
            asmLabel->create<AsmReturnInst>();
          } else if (auto *irBinInst = dyn_cast<BinaryInst>(irInst)) {
            auto reg_res = AsmReg::makeVReg(convertType(irBinInst->getType()));
            auto *asmBinInst = asmLabel->create<AsmBinaryInst>();
            asmBinInst->lhs = lowerValue(irBinInst->getLHS());
            asmBinInst->rhs = lowerValue(irBinInst->getRHS());
            asmBinInst->dst = reg_res;
            valueMap[irBinInst] = reg_res;
          }
        }
      }
    }
  }
};

} // namespace olc
