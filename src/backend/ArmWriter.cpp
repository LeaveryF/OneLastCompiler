#include <olc/backend/ArmWriter.h>

namespace olc {

ArmWriter::Reg::~Reg() {
  if (id < 0)
    return;
  if (isFloat) {
    alloc->fltRegs.insert(id);
  } else {
    alloc->intRegs.insert(id);
  }
}

ArmWriter::Reg::Reg(Reg &&other)
    : isFloat(other.isFloat), id(other.id), alloc(other.alloc) {
  other.id = -1;
}

ArmWriter::Reg &ArmWriter::Reg::operator=(Reg &&other) {
  isFloat = other.isFloat;
  id = other.id;
  alloc = other.alloc;
  other.id = -1;
  return *this;
}

void ArmWriter::printModule(Module *module) {
  os << ".data\n";
  for (auto &global : module->globals) {
    printGlobal(global);
  }

  os << ".text\n";
  os << ".global _start\n";
  for (auto &func : module->functions) {
    os << ".global " << func->fnName << '\n';
  }
  os << R"sss(
_start:
  bl main
  mov r7, #1
  swi 0

)sss";
  for (auto &func : module->functions) {
    printFunc(func);
  }
}

void ArmWriter::printGlobal(GlobalVariable *global) {
  os << global->getName() << ":\n";
  assert(!global->getAllocatedType()->isFloatTy() && "NYI");
  std::function<void(Constant *)> printConst = [&](Constant *val) {
    if (!val) { // zeroinitializer
      unsigned size = 4;
      if (auto *arrTy = dyn_cast<ArrayType>(global->getAllocatedType())) {
        assert(!arrTy->getArrayEltType()->isArrayTy() && "invalid");
        size = 4 * arrTy->getSize();
      }
      os << ".zero " << size << '\n';
    } else if (auto *arr = dyn_cast<ConstantArray>(val)) {
      for (auto *elt : arr->values) {
        printConst(elt);
      }
      os << ".size " << global->getName() << ", " << arr->values.size() * 4
         << '\n';
    } else if (auto *constVal = dyn_cast<ConstantValue>(val)) {
      if (constVal->isInt()) {
        os << ".word " << constVal->getInt() << '\n';
      } else {
        olc_unreachable("HEX float NYI");
      }
    } else {
      olc_unreachable("NYI");
    }
  };
  printConst(global->getInitializer());
}

void ArmWriter::printFunc(Function *function) {
  curFunction = function;
  os << function->fnName << ":\n";

  // 计算栈空间
  stackSize = 0;
  stackMap.clear();
  for (auto *bb : function->basicBlocks) {
    for (auto *instr : bb->instructions) {
      stackMap[instr] = stackSize;
      if (auto *alloca = dyn_cast<AllocaInst>(instr)) {
        if (auto *arrTy = dyn_cast<ArrayType>(alloca->getAllocatedType())) {
          assert(!arrTy->getArrayEltType()->isArrayTy() && "invalid");
          stackSize += 4 * arrTy->getSize();
        } else {
          stackSize += 4;
        }
      } else {
        stackSize += 4;
      }
    }
  }
  printArmInstr("push", {"{r11, lr}"});
  printArmInstr("mov", {"r11", "sp"});
  printArmInstr("sub", {"sp", "sp", "#" + std::to_string(stackSize)});

  if (function->isBuiltin)
    olc_unreachable("NYI");
  for (auto &bb : function->basicBlocks) {
    printBasicBlock(bb);
  }

  os << '\n';
}

void ArmWriter::printBasicBlock(BasicBlock *basicBlock) {
  os << getLabel(basicBlock) << ":\n";
  for (auto instr_it = basicBlock->instructions.begin();
       instr_it != basicBlock->instructions.end(); ++instr_it) {
    printInstr(instr_it);
  }
}

void ArmWriter::printInstr(std::list<Instruction *>::iterator &instr_it) {
  auto &instr = *instr_it;
  switch (instr->tag) {
  case Value::Tag::Alloca:
  case Value::Tag::Load: {
    // Do nothing for naive regalloc
    break;
  }
  case Value::Tag::GetElementPtr: {
    auto *gep = cast<GetElementPtrInst>(instr);
    auto reg_ptr = loadToReg(gep->getPointer());
    if (auto *constIndex = dyn_cast<ConstantValue>(gep->getIndex())) {
      int offset = 4 * constIndex->getInt();
      printArmInstr("add", {reg_ptr, reg_ptr, "#" + std::to_string(offset)});
    } else {
      std::string reg_offset = loadToReg(gep->getIndex());
      printArmInstr("add", {reg_ptr, reg_ptr, reg_offset, "lsl #2"});
    }
    storeRegToMemorySlot(reg_ptr, instr);
    break;
  }
  case Value::Tag::Store: {
    // TODO: consider float register
    auto *storeInst = cast<StoreInst>(instr);
    auto reg_val = loadToReg(storeInst->getValue());
    storeRegToAddress(reg_val, storeInst->getPointer());
    break;
  }
  case Value::Tag::Add:
    printBinInstr("add", instr);
    break;
  case Value::Tag::Sub:
    printBinInstr("sub", instr);
    break;
  case Value::Tag::Mul:
    printBinInstr("mul", instr);
    break;
  case Value::Tag::Div: {
    olc_unreachable("__aeabi_idiv NYI");
    break;
  }
  case Value::Tag::Mod: {
    olc_unreachable("__aeabi_idivmod NYI");
    break;
  }
  case Value::Tag::Lt:
  case Value::Tag::Le:
  case Value::Tag::Ge:
  case Value::Tag::Gt:
  case Value::Tag::Eq:
  case Value::Tag::Ne: {
    // Do nothing, the codegen is in BranchInst
    for (auto &&[user, idx] : instr->uses) {
      assert(isa<BranchInst>(user) && "Cmp result must be used by branch");
    }
    break;
  }
  case Value::Tag::Branch: {
    auto *brInst = cast<BranchInst>(instr);
    auto *cond = dyn_cast<BinaryInst>(brInst->getCondition());
    assert(cond && cond->isCmpOp() && "Branch condition must be a cmp op");
    auto condTag = getCondTagStr(cond->tag);
    printCmpInstr(cond);
    printArmInstr(
        "b" + condTag, {getLabel(cast<BranchInst>(instr)->getTrueBlock())});
    printArmInstr("b", {getLabel(cast<BranchInst>(instr)->getFalseBlock())});
    break;
    break;
  }
  case Value::Tag::Jump:
    printArmInstr("b", {getLabel(cast<JumpInst>(instr)->getTargetBlock())});
    break;
  case Value::Tag::Return: {
    auto *retInst = cast<ReturnInst>(instr);
    // if not ret void
    // TODO: consider float type
    Reg reg_ret = regAlloc.claimIntReg(0);
    if (retInst->getNumOperands() == 1)
      assignToSpecificReg(reg_ret, retInst->getReturnValue());
    printArmInstr("mov", {"sp", "r11"});
    printArmInstr("pop", {"{r11, lr}"});
    printArmInstr("bx", {"lr"});
    break;
  }
  case Value::Tag::Call: {
    auto *callInst = cast<CallInst>(instr);
    assert(callInst->getArgs().size() < 4 && "NYI");
    std::vector<Reg> callRegs;
    callRegs.emplace_back(regAlloc.claimIntReg(0));
    for (unsigned i = 1; i < callInst->getArgs().size(); i++)
      callRegs.emplace_back(regAlloc.claimIntReg(i));

    // TODO: consider float

    for (unsigned i = 0; i < callInst->getArgs().size(); i++) {
      assignToSpecificReg(callRegs[i], callInst->getArgs()[i]);
    }
    printArmInstr("bl", {callInst->getCallee()->fnName});
    storeRegToMemorySlot(callRegs[0], instr);
    break;
  }
  default:
    std::cerr << "NYI Instruction tag: " << static_cast<int>(instr->tag)
              << "\n";
    olc_unreachable("NYI");
    break;
  }
}

void ArmWriter::printArmInstr(
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

void ArmWriter::printBinInstr(const std::string &op, Instruction *instr) {
  auto reg_lhs = loadToReg(instr->getOperand(0));
  auto reg_rhs = loadToReg(instr->getOperand(1));
  printArmInstr(op, {reg_lhs, reg_lhs, reg_rhs});
  storeRegToMemorySlot(reg_lhs, instr);
}

void ArmWriter::printCmpInstr(BinaryInst *instr) {
  // TODO: utilize Operand2 to handle immediate
  auto reg_lhs = loadToReg(instr->getOperand(0));
  auto reg_rhs = loadToReg(instr->getOperand(1));
  printArmInstr("cmp", {reg_lhs, reg_rhs});
}

std::string ArmWriter::getStackOper(Value *val) {
  if (auto *ld = dyn_cast<LoadInst>(val))
    val = ld->getPointer();
  return "[sp, #" + std::to_string(stackMap.at(val)) + "]";
}

std::string ArmWriter::getImme(ConstantValue *val) { // TODO: float
  if (val->isInt()) {
    return "#" + std::to_string(val->getInt());
  } else {
    // TODO: ensure it is correct
    return "#" + std::to_string(val->getFloat());
  }
}

std::string ArmWriter::getLabel(BasicBlock *bb) {
  if (labelMap.find(bb) == labelMap.end()) {
    labelMap[bb] = labelMap.size();
  }
  return "." + bb->label + "_" + std::to_string(labelMap[bb]);
}

} // namespace olc
