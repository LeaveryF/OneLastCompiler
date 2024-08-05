#include <olc/backend/ArmWriter.h>

namespace olc {

void ArmWriter::printModule(Module *module) {
  os << ".data\n";
  for (auto &global : module->globals) {
    printGlobal(global);
  }

  os << ".text\n";
  os << ".global _start\n";
  for (auto &func : module->functions) {
    printFunc(func);
  }
}

void ArmWriter::printGlobal(GlobalVariable *global) {
  // TODO: data section
  os << "\n";
}

void ArmWriter::printFunc(Function *function) {
  if (function->fnName == "main") {
    os << "_start:\n";
  } else {
    os << function->fnName << ":\n";
  }

  // 计算栈空间
  stackSize = 0;
  curReg = 1;
  stackMap.clear();
  for (auto *bb : function->basicBlocks) {
    for (auto *instr : bb->instructions) {
      if (instr->tag == Value::Tag::Alloca ||
          instr->isDefVar() && instr->tag != Value::Tag::Load) {
        stackMap[instr] = stackSize; // TODO: array
        stackSize += 4;
      }
    }
  }
  printArmInstr("push", {"{r11, lr}"});
  printArmInstr("mov", {"r11", "sp"});
  printArmInstr("sub", {"sp", "sp", "#" + std::to_string(stackSize)});

  paramCnt = 0;
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
    auto reg_offset = getImme(gep->getIndex());
    printArmInstr("add", {reg_ptr, reg_ptr, reg_offset});
    storeRegToMemorySlot(reg_ptr, instr);
    break;
  }
  case Value::Tag::Store: {
    // TODO: consider float register
    auto *storeInst = cast<StoreInst>(instr);
    auto reg_val = loadToReg(storeInst->getValue());
    auto reg_ptr = loadToReg(storeInst->getPointer());
    printArmInstr("str", {reg_val, "[" + reg_ptr + "]"});
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
  case Value::Tag::Div:
    printBinInstr("div", instr);
    break;
  case Value::Tag::Mod:
    // TODO: mod
    break;
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
    switch (cond->tag) {
    case Value::Tag::Lt:
      auto condTag = getCondTagStr(cond->tag);
      printCmpInstr(cond);
      printArmInstr(
          "b" + condTag, {getLabel(cast<BranchInst>(instr)->getTrueBlock())});
      printArmInstr("b", {getLabel(cast<BranchInst>(instr)->getFalseBlock())});
      break;
    }
    break;
  }
  case Value::Tag::Jump:
    printArmInstr("b", {getLabel(cast<JumpInst>(instr)->getTargetBlock())});
    break;
  case Value::Tag::Return: {
    auto *retInst = cast<ReturnInst>(instr);
    // if not ret void
    if (retInst->getNumOperands() == 1)
      loadToSpecificReg("r0", retInst->getReturnValue());
    printArmInstr("mov", {"sp", "r11"});
    printArmInstr("pop", {"{r11, lr}"});
    printArmInstr("bx", {"lr"});
    break;
  }
  case Value::Tag::Call: {
    curReg = 0; // TODO: more params
    for (auto *arg : cast<CallInst>(instr)->getArgs()) {
      printArmInstr("str", {getReg(), getStackOper(arg)});
    }
    printArmInstr("bl", {cast<CallInst>(instr)->getCallee()->fnName});
    break;
  }
  default:
    std::cerr << "NYI Instruction tag: " << static_cast<int>(instr->tag)
              << "\n";
    olc_unreachable("NYI");
    break;
  }
  // Drop all register values. We have already store the value to stack.
  regAlloc.reset();
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
  printBinInstr("cmp", instr);
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

std::string ArmWriter::getReg() {
  if (curReg >= 11) {
    curReg = 0;
  }
  return "r" + std::to_string(curReg++);
}

std::string ArmWriter::getLabel(BasicBlock *bb) {
  if (labelMap.find(bb) == labelMap.end()) {
    labelMap[bb] = labelMap.size();
  }
  return "." + bb->label + "_" + std::to_string(labelMap[bb]);
}

} // namespace olc
