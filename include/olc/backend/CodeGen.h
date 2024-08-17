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

  template <AsmImm::LoadMethod method = AsmImm::AlwaysReg>
  AsmValue *lowerImm(int32_t value, AsmLabel *label) {
    bool useReg = method == AsmImm::AlwaysReg || !AsmImm::match<method>(value);
    if (useReg) {
      return loadImmToReg(new AsmImm{value}, label);
    } else {
      return new AsmImm{value};
    }
  }

  template <AsmImm::LoadMethod method = AsmImm::AlwaysReg>
  AsmValue *lowerImm(float value, AsmLabel *label) {
    // float should always use register
    return loadImmToReg(
        new AsmImm{AsmImm::getBitRepr(value)}, label, AsmType::F32);
  }

  AsmReg *
  loadImmToReg(AsmImm *imm, AsmLabel *label, AsmType type = AsmType::I32) {
    auto asmReg = AsmReg::makeVReg(AsmType::I32);
    auto *asmMovInst = new AsmMoveInst{};
    asmMovInst->src = imm;
    asmMovInst->dst = asmReg;
    assert(label);
    label->push_back(asmMovInst);
    if (type == AsmType::F32) {
      auto asmRegF = AsmReg::makeVReg(AsmType::F32);
      auto *asmMovInstF = new AsmMoveInst{};
      asmMovInstF->src = asmReg;
      asmMovInstF->dst = asmRegF;
      label->push_back(asmMovInstF);
      return asmRegF;
    }
    return asmReg;
  }

  template <AsmImm::LoadMethod method = AsmImm::AlwaysReg>
  AsmValue *lowerValue(Value *value, AsmLabel *label) {
    if (auto *irConst = dyn_cast<ConstantValue>(value)) {
      if (irConst->isInt()) {
        return lowerImm<method>(irConst->getInt(), label);
      } else {
        return lowerImm<method>(irConst->getFloat(), label);
      }
    } else if (auto *irGlobal = dyn_cast<GlobalVariable>(value)) {
      auto *ldGlbInst = new AsmLoadGlobalInst{};
      ldGlbInst->dst = AsmReg::makeVReg(AsmType::I32);
      ldGlbInst->var = irGlobal;
      assert(label);
      label->push_back(ldGlbInst);
      return ldGlbInst->dst;
    } else {
      return valueMap.at(value);
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
      if (arg->getType()->isFloatTy()) {
        if (info.argsInFloatReg.size() < maxFloatRegs) {
          info.argsInFloatReg.push_back(arg);
        } else {
          info.argsOnStack.push_back(arg);
        }
      } else {
        if (info.argsInIntReg.size() < maxIntRegs) {
          info.argsInIntReg.push_back(arg);
        } else {
          info.argsOnStack.push_back(arg);
        }
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
        // 声明参数的栈空间
        // 这里先使用 sp, (i-4)*4，等 stackSize 与 pushSize 固定后
        // 将其替换为 sp, stackSize + pushSize + (i-4)*4
        int argsOffset = argsOnStack.size() % 2 ? 4 : 0;
        for (const auto &argOnStack : argsOnStack) {
          // add rx, sp, (n-i)*4
          auto reg_tmp = AsmReg::makeVReg(AsmType::I32);
          auto *spOffsetInst = new AsmMoveInst{};
          spOffsetInst->src = lowerImm<AsmImm::Imm32bit>(argsOffset, asmEntry);
          spOffsetInst->dst = reg_tmp;
          asmEntry->push_back(spOffsetInst);
          // 保存以备后续替换计算真实偏移
          asmFunc->stackArgOffsets.push_back(spOffsetInst);
          // ldr reg_res, [sp, reg_tmp]
          auto reg_res = AsmReg::makeVReg(convertType(argOnStack->getType()));
          auto *asmLoadInst = new AsmLoadInst{};
          asmLoadInst->addr = PReg::sp();
          asmLoadInst->offset = reg_tmp;
          asmLoadInst->dst = reg_res;
          asmEntry->push_back(asmLoadInst);
          valueMap[argOnStack] = reg_res;
          argsOffset += 4;
        }
      }

      for (auto *irBB : irFunc->basicBlocks) {
        auto asmLabel = labelMap.at(irBB);
        for (auto *irInst : irBB->instructions) {
          if (auto *irRetInst = dyn_cast<ReturnInst>(irInst)) {
            auto *asmRetInst = new AsmReturnInst{};
            if (auto *retVal = irRetInst->getReturnValue()) {
              // mov r0 / s0, value
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(retVal, asmLabel);
              asmMovInst->dst =
                  AsmReg::makePReg(convertType(retVal->getType()), 0);
              asmLabel->push_back(asmMovInst);
              asmLabel->terminatorBegin = asmMovInst;
            } else {
              asmLabel->terminatorBegin = asmRetInst;
            }
            asmLabel->push_back(asmRetInst);
          } else if (auto *irBinInst = dyn_cast<BinaryInst>(irInst)) {
            auto reg_res = AsmReg::makeVReg(convertType(irBinInst->getType()));
            auto opTag = convertBinOpTag(irBinInst->tag);
            if (opTag == AsmBinaryInst::Tag::Cmp) {
              auto *asmCmpInst = new AsmCompareInst{};
              asmCmpInst->lhs = lowerValue(irBinInst->getLHS(), asmLabel);
              asmCmpInst->rhs =
                  lowerValue<AsmImm::Operand2>(irBinInst->getRHS(), asmLabel);
              asmLabel->push_back(asmCmpInst);
              bool allUseIsBr = std::all_of(
                  irBinInst->uses.begin(), irBinInst->uses.end(),
                  [&](Use const &use) { return isa<BranchInst>(use.user); });
              if (!allUseIsBr) {
                auto *dst = AsmReg::makeVReg(AsmType::I32);

                // mov#cond r0, 1
                auto *asmMovTrue = new AsmMoveInst{};
                asmMovTrue->src = lowerImm<AsmImm::Imm32bit>(1, asmLabel);
                asmMovTrue->dst = dst;
                asmMovTrue->pred = convertAsmPredTag(irBinInst->tag);
                asmLabel->push_back(asmMovTrue);
                // mov#cond r0, 0
                auto *asmMovFalse = new AsmMoveInst{};
                asmMovFalse->src = lowerImm<AsmImm::Imm32bit>(0, asmLabel);
                asmMovFalse->dst = dst;
                asmMovFalse->pred =
                    getNotAsmPred(convertAsmPredTag(irBinInst->tag));
                asmLabel->push_back(asmMovFalse);

                valueMap[irBinInst] = asmMovTrue->dst;
              }
            } else {
              auto *asmBinInst = new AsmBinaryInst{opTag};
              // TODO: optimize with immediates
              asmBinInst->lhs = lowerValue(irBinInst->getLHS(), asmLabel);
              // add and sub allows Operand2, but mul and sdiv requires reg
              if (opTag == AsmBinaryInst::Tag::Add ||
                  opTag == AsmBinaryInst::Tag::Sub) {
                asmBinInst->rhs =
                    lowerValue<AsmImm::Operand2>(irBinInst->getRHS(), asmLabel);
              } else {
                asmBinInst->rhs = lowerValue(irBinInst->getRHS(), asmLabel);
              }
              asmBinInst->dst = reg_res;
              valueMap[irBinInst] = reg_res;
              asmLabel->push_back(asmBinInst);
            }
          } else if (auto *irAllocaInst = dyn_cast<AllocaInst>(irInst)) {
            auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Add};
            spOffsetInst->lhs = AsmReg::sp();
            spOffsetInst->rhs =
                lowerImm<AsmImm::Operand2>(asmFunc->stackSize, asmLabel);
            spOffsetInst->dst = AsmReg::makeVReg(AsmType::I32);
            valueMap[irAllocaInst] = spOffsetInst->dst;
            asmFunc->stackSize += irAllocaInst->getAllocatedSize();
            asmLabel->push_back(spOffsetInst);
          } else if (auto *irLoadInst = dyn_cast<LoadInst>(irInst)) {
            auto reg_res = AsmReg::makeVReg(convertType(irLoadInst->getType()));
            auto *asmLoadInst = new AsmLoadInst{};
            if (reg_res->type == AsmType::F32)
              asmLoadInst->addr = lowerValue<AsmImm::Imm8bitx4>(
                  irLoadInst->getPointer(), asmLabel);
            else
              asmLoadInst->addr = lowerValue<AsmImm::Imm12bit>(
                  irLoadInst->getPointer(), asmLabel);
            asmLoadInst->dst = reg_res;
            valueMap[irLoadInst] = reg_res;
            asmLabel->push_back(asmLoadInst);
          } else if (auto *irStoreInst = dyn_cast<StoreInst>(irInst)) {
            // TODO:
            auto reg_src = lowerValue(irStoreInst->getValue(), asmLabel);
            auto *asmStoreInst = new AsmStoreInst{};
            if (convertType(irStoreInst->getValue()->getType()) == AsmType::F32)
              asmStoreInst->addr = lowerValue<AsmImm::Imm8bitx4>(
                  irStoreInst->getPointer(), asmLabel);
            else
              asmStoreInst->addr = lowerValue<AsmImm::Imm12bit>(
                  irStoreInst->getPointer(), asmLabel);
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
              asmMovInst->src = lowerValue(argsInIntRegs[i], asmLabel);
              auto *preg = AsmReg::makePReg(AsmType::I32, i);
              asmMovInst->dst = preg;
              asmCallInst->callUses.insert(preg);
              asmLabel->push_back(asmMovInst);
            }
            for (unsigned i = 0; i < argsInFloatRegs.size(); i++) {
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = lowerValue(argsInFloatRegs[i], asmLabel);
              auto *preg = AsmReg::makePReg(AsmType::F32, i);
              asmMovInst->dst = preg;
              asmCallInst->callUses.insert(preg);
              asmLabel->push_back(asmMovInst);
            }
            // 栈传参，倒序压栈
            const int totalArgsSpace = argsOnStack.size() * 4;
            int argsOffset = 0;
            for (const auto &argOnStack : argsOnStack) {
              // sub rx, sp, (n-i)*4
              auto *spOffsetInst = new AsmBinaryInst{AsmInst::Tag::Sub};
              spOffsetInst->lhs = AsmReg::sp();
              spOffsetInst->rhs = lowerImm<AsmImm::Operand2>(
                  totalArgsSpace - argsOffset, asmLabel);
              spOffsetInst->dst = AsmReg::makeVReg(AsmType::I32);
              asmLabel->push_back(spOffsetInst);
              // str value, [rx]
              auto *asmStoreInst = new AsmStoreInst{};
              asmStoreInst->addr = spOffsetInst->dst;
              asmStoreInst->src = lowerValue(argOnStack, asmLabel);
              asmLabel->push_back(asmStoreInst);
              argsOffset += 4;
            }
            // 对齐到 8
            if (argsOffset % 8 != 0) {
              argsOffset += 4;
            }
            if (totalArgsSpace != 0) {
              assert(argsOffset > 0);
              // sub sp, sp, (n-4)*4
              auto *subInst = new AsmBinaryInst{AsmInst::Tag::Sub};
              subInst->lhs = AsmReg::sp();
              subInst->rhs = lowerImm<AsmImm::Operand2>(argsOffset, asmLabel);
              subInst->dst = AsmReg::sp();
              asmLabel->push_back(subInst);
            }
            // bl func
            asmLabel->push_back(asmCallInst);
            if (totalArgsSpace != 0) {
              assert(argsOffset > 0);
              // add sp, sp, (n-4)*4
              auto *addInst = new AsmBinaryInst{AsmInst::Tag::Add};
              addInst->lhs = AsmReg::sp();
              addInst->rhs = lowerImm<AsmImm::Operand2>(argsOffset, asmLabel);
              addInst->dst = AsmReg::sp();
              asmLabel->push_back(addInst);
            }
            // 返回值 mov value, r0 / s0
            if (!irCallInst->getType()->isVoidTy()) {
              auto *preg =
                  AsmReg::makePReg(convertType(irCallInst->getType()), 0);
              asmCallInst->callDefs.insert(preg);
              auto reg_ret =
                  AsmReg::makeVReg(convertType(irCallInst->getType()));
              auto *asmMovInst = new AsmMoveInst{};
              asmMovInst->src = preg;
              asmMovInst->dst = reg_ret;
              asmLabel->push_back(asmMovInst);
              valueMap[irCallInst] = reg_ret;
            }
          } else if (auto *irGEPInst = dyn_cast<GetElementPtrInst>(irInst)) {
            auto *addr = lowerValue(irGEPInst->getPointer(), asmLabel);
            // Load it to immediate anyway, we have other logic below.
            auto *offset =
                lowerValue<AsmImm::Imm32bit>(irGEPInst->getIndex(), asmLabel);
            auto *asmBinInst = new AsmBinaryInst{AsmInst::Tag::Add};
            asmBinInst->lhs = addr;
            asmBinInst->dst =
                AsmReg::makeVReg(convertType(irGEPInst->getType()));
            // word size is 4, the offset must x4
            // if imm, just calc it; if reg, use lsl #2
            if (auto *immOffset = dyn_cast<AsmImm>(offset)) {
              if (auto offsetx4 = immOffset->hexValue * 4;
                  AsmImm::match<AsmImm::Operand2>(offsetx4))
                asmBinInst->rhs = new AsmImm{offsetx4};
              else
                asmBinInst->rhs = lowerImm((int)immOffset->hexValue, asmLabel);
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
            asmLabel->terminatorBegin = branchInst;
          } else if (auto *irJumpInst = dyn_cast<JumpInst>(irInst)) {
            // 处理无条件跳转指令
            auto *jumpInst = new AsmJumpInst{nullptr};
            jumpInst->target = labelMap.at(irJumpInst->getTargetBlock());
            asmLabel->push_back(jumpInst);
            asmLabel->terminatorBegin = jumpInst;
          } else if (auto *i2fInst = dyn_cast<IntToFloatInst>(irInst)) {
            auto ireg = lowerValue(i2fInst->getIntValue(), asmLabel);
            auto freg = AsmReg::makeVReg(AsmType::F32);
            auto *asmMovInst = new AsmMoveInst{};
            asmMovInst->src = ireg;
            asmMovInst->dst = freg;
            asmLabel->push_back(asmMovInst);
            auto *asmCvtInst = new AsmConvertInst{AsmConvertInst::CvtType::i2f};
            asmCvtInst->src = freg;
            asmCvtInst->dst = freg;
            asmLabel->push_back(asmCvtInst);
            valueMap[i2fInst] = freg;
          } else if (auto *f2iInst = dyn_cast<FloatToIntInst>(irInst)) {
            auto freg = lowerValue(f2iInst->getFloatValue(), asmLabel);
            auto ireg = AsmReg::makeVReg(AsmType::I32);
            auto *asmCvtInst = new AsmConvertInst{AsmConvertInst::CvtType::f2i};
            asmCvtInst->src = freg;
            asmCvtInst->dst = freg;
            asmLabel->push_back(asmCvtInst);
            auto *asmMovInst = new AsmMoveInst{};
            asmMovInst->src = freg;
            asmMovInst->dst = ireg;
            asmLabel->push_back(asmMovInst);
            valueMap[f2iInst] = ireg;
          } else if (auto *phiInst = dyn_cast<PhiInst>(irInst)) {
            // Just create a vreg for it. Phi is handled later.
            auto *vreg = AsmReg::makeVReg(convertType(phiInst->getType()));
            valueMap[phiInst] = vreg;
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

      // Phi nodes
      for (auto *irBB : irFunc->basicBlocks) {
        auto *asmLabel = labelMap.at(irBB);

        // Pair<dst, src>
        using PMove = std::vector<std::pair<AsmValue *, AsmValue *>>;
        // Multiple allocas result in PMove semantically.
        // PMove phiMove;
        // Prepare values in vregs for consuming of phi pmove.
        std::map<AsmLabel *, PMove> predMoves;

        for (auto *irInst : irBB->instructions) {
          if (auto *phiInst = dyn_cast<PhiInst>(irInst)) {
            auto *phiVreg = lowerValue(phiInst, asmLabel);
            for (unsigned i = 0; i < phiInst->getNumIncomingValues(); i++) {
              auto *pred = phiInst->getIncomingBlock(i);
              auto *value = phiInst->getIncomingValue(i);
              if (isa<Undef>(value))
                continue;
              auto *predLabel = labelMap.at(pred);
              auto *predValue = lowerValue<AsmImm::Imm32bit>(value, nullptr);
              predMoves[predLabel].push_back({phiVreg, predValue});
            }
          } else
            break;
        }

        for (auto &[pred, moves] : predMoves) {
          for (auto &[dst, src] : moves) {
            auto *pMove = new AsmMoveInst{};
            pMove->src = src;
            pMove->dst = dst;
            assert(pred->terminatorBegin && "Should have terminator");
            pred->push_before(pred->terminatorBegin, pMove);
          }
        }
      }
    }
  }
};

} // namespace olc
