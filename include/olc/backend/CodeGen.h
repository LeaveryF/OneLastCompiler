#pragma once

#include <olc/Support.h>

#include <olc/backend/MachineIR.h>
#include <olc/ir/IR.h>

#include <map>
#include <vector>

namespace olc {

struct CodeGen {

  Module *irModule = nullptr;
  AsmModule *asmModule = nullptr;
  std::map<Value *, AsmValue *> valueMap;
  std::map<Function *, AsmFunc *> fnMap;
  std::map<BasicBlock *, AsmLabel *> labelMap;

  CodeGen(Module *module) : irModule(module), asmModule(new AsmModule{}) {}

  AsmPredicate convertAsmPredTag(Value::Tag tag) {
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

  AsmPredicate getNotAsmPred(AsmPredicate pred) {
    switch (pred) {
    case AsmPredicate::Lt:
      return AsmPredicate::Ge;
    case AsmPredicate::Le:
      return AsmPredicate::Gt;
    case AsmPredicate::Gt:
      return AsmPredicate::Le;
    case AsmPredicate::Ge:
      return AsmPredicate::Lt;
    case AsmPredicate::Eq:
      return AsmPredicate::Ne;
    case AsmPredicate::Ne:
      return AsmPredicate::Eq;
    default:
      olc_unreachable("invalid pred");
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
      auto *ldGlbInst = new AsmLoadGlobalInst{};
      ldGlbInst->dst = AsmReg::makeVReg(AsmType::I32);
      ldGlbInst->var = irGlobal;
      label->push_back(ldGlbInst);
      return ldGlbInst->dst;
    } else {
      return valueMap.at(value);
    }
  }

  // Immediate is always loaded into a I32 reg. If we need load float immediate,
  // we should insert an extra `vmov.f32 s0, r0` instruction.
  AsmReg *loadImmToReg(AsmImm *imm, AsmLabel *label) {
    auto asmReg = AsmReg::makeVReg(AsmType::I32);
    auto *asmMovInst = new AsmMoveInst{};
    asmMovInst->src = imm;
    asmMovInst->dst = asmReg;
    label->push_back(asmMovInst);
    return asmReg;
  }

  AsmReg *lowerValueToReg(Value *value, AsmLabel *label) {
    auto *asmValue = lowerValue(value, label);
    if (auto *asmReg = dyn_cast<AsmReg>(asmValue)) {
      return asmReg;
    }
    if (value->getType()->isFloatTy())
      olc_unreachable("Float imm NYI, see the comment of loadImmToReg");
    return loadImmToReg(cast<AsmImm>(asmValue), label);
  }

  struct CallInfo {
    std::vector<Value *> argsInIntReg, argsInFloatReg;
    std::vector<Value *> argsOnStack;
  };

  template <typename T>
  auto arrangeCallInfo(std::vector<T> const &args) -> CallInfo {
    CallInfo info{};
    for (auto const &rarg : args) {
      auto arg = cast<Value>(rarg);
      if (arg->getType()->isIntegerTy() && info.argsInIntReg.size() < 4) {
        info.argsInIntReg.push_back(arg);
      } else if (
          arg->getType()->isFloatTy() && info.argsInFloatReg.size() < 16) {
        info.argsInFloatReg.push_back(arg);
      } else {
        info.argsOnStack.push_back(arg);
      }
    }
    return info;
  }

  void run() {
    for (auto *irGlobal : irModule->globals) {
      asmModule->globals.push_back(irGlobal);
    }

    for (auto *irFunc : irModule->functions) {
      auto asmFunc = new AsmFunc{irFunc->fnName};
      asmFunc->isBuiltin = irFunc->isBuiltin;
      fnMap[irFunc] = asmFunc;
      asmModule->funcs.push_back(asmFunc);
      auto args = irFunc->args;
      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = new AsmLabel{irBB->label};
        labelMap[irBB] = asmLabel;
        asmFunc->labels.push_back(asmLabel);
      }
      auto asmEntry = labelMap.at(irFunc->getEntryBlock());

      {
        auto loadPRegToVReg = [&](AsmReg *preg) {
          auto *vreg = AsmReg::makeVReg(preg->type);
          auto *asmMovInst = new AsmMoveInst{};
          asmMovInst->src = preg;
          asmMovInst->dst = vreg;
          asmEntry->push_back(asmMovInst);
          return vreg;
        };

        auto &&[argsInIntReg, argsInFloatReg, argsOnStack] =
            arrangeCallInfo(args);
        for (unsigned i = 0; i < argsInIntReg.size(); i++) {
          auto *arg = cast<Argument>(argsInIntReg[i]);
          auto *preg = AsmReg::makePReg(AsmType::I32, i);
          valueMap[arg] = loadPRegToVReg(preg);
        }
        for (unsigned i = 0; i < argsInFloatReg.size(); i++) {
          auto *arg = cast<Argument>(argsInFloatReg[i]);
          auto *preg = AsmReg::makePReg(AsmType::F32, i);
          valueMap[arg] = loadPRegToVReg(preg);
        }
        for (auto *rarg : argsOnStack) {
          // 声明参数的栈空间 ldr value, [sp, #(n-i)*4], i = 0..n-1
          int argsOffset = argsOnStack.size() * 4;
          for (const auto &argOnStack : argsOnStack) {
            // add rx, sp, (n-i)*4
            auto reg_tmp = AsmReg::makeVReg(AsmType::I32);
            auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Add};
            spOffsetInst->lhs = AsmReg::sp();
            spOffsetInst->rhs = lowerImm(argsOffset);
            spOffsetInst->dst = reg_tmp;
            asmEntry->push_back(spOffsetInst);
            valueMap[argOnStack] = reg_tmp;
            // ldr ry, [rx]
            auto reg_res = AsmReg::makeVReg(convertType(argOnStack->getType()));
            auto *asmLoadInst = new AsmLoadInst{};
            asmLoadInst->addr = lowerValue(argOnStack, asmEntry);
            asmLoadInst->dst = reg_res;
            asmEntry->push_back(asmLoadInst);
            valueMap[argOnStack] = reg_res;
            argsOffset -= 4;
          }
        }
      }

      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = labelMap.at(irBB);
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
            auto opTag = convertBinOpTag(irBinInst->tag);
            if (opTag == AsmBinaryInst::Tag::Cmp) {
              auto *asmCmpInst = new AsmCompareInst{};
              asmCmpInst->lhs = lowerValueToReg(irBinInst->getLHS(), asmLabel);
              asmCmpInst->rhs = lowerValueToReg(irBinInst->getRHS(), asmLabel);
              asmLabel->push_back(asmCmpInst);
              bool allUseIsBr = std::all_of(
                  irBinInst->uses.begin(), irBinInst->uses.end(),
                  [&](Use const &use) { return isa<BranchInst>(use.user); });
              if (!allUseIsBr) {
                auto *dst = AsmReg::makeVReg(AsmType::I32);

                // mov#cond r0, 1
                auto *asmMovTrue = new AsmMoveInst{};
                asmMovTrue->src = lowerImm(1);
                asmMovTrue->dst = dst;
                asmMovTrue->pred = convertAsmPredTag(irBinInst->tag);
                asmLabel->push_back(asmMovTrue);
                // mov#cond r0, 0
                auto *asmMovFalse = new AsmMoveInst{};
                asmMovFalse->src = lowerImm(0);
                asmMovFalse->dst = dst;
                asmMovFalse->pred = getNotAsmPred(convertAsmPredTag(irBinInst->tag));
                asmLabel->push_back(asmMovFalse);

                valueMap[irBinInst] = asmMovTrue->dst;
              }
            } else {
              auto *asmBinInst = new AsmBinaryInst{opTag};
              // TODO: optimize with immediates
              asmBinInst->lhs = lowerValueToReg(irBinInst->getLHS(), asmLabel);
              asmBinInst->rhs = lowerValueToReg(irBinInst->getRHS(), asmLabel);
              asmBinInst->dst = reg_res;
              valueMap[irBinInst] = reg_res;
              asmLabel->push_back(asmBinInst);
            }
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
            auto *asmCallInst =
                new AsmCallInst{irCallInst->getCallee()->fnName};
            auto args = irCallInst->getArgs();

            auto &&[argsInIntRegs, argsInFloatRegs, argsOnStack] =
                arrangeCallInfo(args);
            // 寄存器传参 r0-r3 / s0-s15  mov ri, value
            for (unsigned i = 0; i < argsInIntRegs.size(); i++) {
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(args[i], asmLabel);
              auto *preg = AsmReg::makePReg(convertType(args[i]->getType()), i);
              asmMovInst->dst = preg;
              asmCallInst->callUses.insert(preg);
              asmLabel->push_back(asmMovInst);
            }
            for (unsigned i = 0; i < argsInFloatRegs.size(); i++) {
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(args[i], asmLabel);
              auto *preg = AsmReg::makePReg(convertType(args[i]->getType()), i);
              asmMovInst->dst = preg;
              asmCallInst->callUses.insert(preg);
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
            asmLabel->push_back(asmCallInst);
            // add sp, sp, (n-4)*4
            auto *addInst = new AsmBinaryInst{AsmInst::Tag::Add};
            addInst->lhs = AsmReg::sp();
            addInst->rhs = lowerImm(argsOffset);
            addInst->dst = AsmReg::sp();
            // 返回值 mov value, r0 / s0
            if (!irCallInst->getType()->isVoidTy()) {
              auto *preg =
                  AsmReg::makePReg(convertType(irCallInst->getType()), 0);
              asmCallInst->callDefs.insert(preg);
              valueMap[irCallInst] = preg;
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = preg;
              asmMovInst->dst = lowerValue(irCallInst, asmLabel);
              asmLabel->push_back(asmMovInst);
            }
          } else if (auto *irGEPInst = dyn_cast<GetElementPtrInst>(irInst)) {
            auto *addr = lowerValueToReg(irGEPInst->getPointer(), asmLabel);
            auto *offset = lowerValue(irGEPInst->getIndex(), asmLabel);
            auto *asmBinInst = new AsmBinaryInst{AsmInst::Tag::Add};
            asmBinInst->lhs = addr;
            asmBinInst->dst =
                AsmReg::makeVReg(convertType(irGEPInst->getType()));
            // word size is 4, the offset must x4
            // if imm, just calc it; if reg, use lsl #2
            if (auto *immOffset = dyn_cast<AsmImm>(offset)) {

              if (immOffset->hexValue * 4 < 4096)
                asmBinInst->rhs = new AsmImm{immOffset->hexValue * 4};
              else
                asmBinInst->rhs = loadImmToReg(immOffset, asmLabel);
            } else {
              asmBinInst->rhs = offset;
            }
            if (!isa<AsmImm>(asmBinInst->rhs)) {
              asmBinInst->shift = 2;
            }

            asmLabel->push_back(asmBinInst);
            valueMap[irGEPInst] = asmBinInst->dst;
          } else if (auto *irBranchInst = dyn_cast<BranchInst>(irInst)) {
            // 处理分支指令
            auto *branchInst = new AsmBranchInst{};
            auto *cond = dyn_cast<BinaryInst>(irBranchInst->getCondition());
            branchInst->pred = convertAsmPredTag(cond->tag);
            branchInst->trueTarget = labelMap.at(irBranchInst->getTrueBlock());
            branchInst->falseTarget =
                labelMap.at(irBranchInst->getFalseBlock());
            asmLabel->push_back(branchInst);
          } else if (auto *irJumpInst = dyn_cast<JumpInst>(irInst)) {
            // 处理无条件跳转指令
            auto *jumpInst = new AsmJumpInst{nullptr};
            jumpInst->target = labelMap.at(irJumpInst->getTargetBlock());
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
