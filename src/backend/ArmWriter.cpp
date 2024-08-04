#include <olc/backend/ArmWriter.h>

#include <algorithm>

namespace olc {

void ArmWriter::printModule(Module *module) {
  os << ".data\n";
  for (auto &global : module->globals) {
    printGlobal(global);
  }

  os << ".text\n";
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
          instr->tag >= Value::Tag::BeginBinOp &&
              instr->tag <= Value::Tag::EndBinOp) {
        stackMap[instr] = stackSize; // TODO: array
        stackSize += 4;
      }
    }
  }
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
  case Value::Tag::Load: {
    // Do nothing for naive regalloc
    break;
  }
  case Value::Tag::Store:
    if (auto *arg = dyn_cast<Argument>(instr->getOperand(0))) {
      printArmInstr("str", {getReg(), getStackOper(instr->getOperand(1))});
    } else if (auto *constVal = dyn_cast<ConstantValue>(instr->getOperand(0))) {
      printArmInstr("mov", {"r0", getImme(constVal)});
      printArmInstr("str", {"r0", getStackOper(instr->getOperand(1))});
    } else {
      printArmInstr("str", {"r0", getStackOper(instr->getOperand(1))});
    }
    break;
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
  case Value::Tag::Return:
    if (cast<ReturnInst>(instr)->getNumOperands() == 1) {
      printArmInstr(
          "mov",
          {"r0", getFromValue(cast<ReturnInst>(instr)->getReturnValue())});
    }
    printArmInstr("add", {"sp", "sp", "#" + std::to_string(stackSize)});
    printArmInstr("bx", {"lr"});
    break;
  case Value::Tag::Call:
    curReg = 0; // TODO: more params
    for (auto *arg : cast<CallInst>(instr)->getArgs()) {
      printArmInstr("str", {getReg(), getStackOper(arg)});
    }
    printArmInstr("bl", {cast<CallInst>(instr)->getCallee()->fnName});
    break;
  default:
    // olc_unreachable("NYI");
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
  if (auto *constVal = dyn_cast<ConstantValue>(instr->getOperand(0))) {
    printArmInstr("mov", {"r1", getImme(constVal)});
  } else {
    printArmInstr("ldr", {"r1", getStackOper(instr->getOperand(0))});
  }
  if (auto *constVal = dyn_cast<ConstantValue>(instr->getOperand(1))) {
    printArmInstr("mov", {"r2", getImme(constVal)});
  } else {
    printArmInstr("ldr", {"r2", getStackOper(instr->getOperand(1))});
  }
  printArmInstr(op, {"r0", "r1", "r2"});
  printArmInstr("str", {"r0", getStackOper(instr)});
}

void ArmWriter::printCmpInstr(BinaryInst *instr) {
  // TODO: utilize Operand2 to handle immediate
  if (auto *constVal = dyn_cast<ConstantValue>(instr->getLHS())) {
    printArmInstr("mov", {"r1", getImme(constVal)});
  } else {
    printArmInstr("ldr", {"r1", getStackOper(instr->getLHS())});
  }
  if (auto *constVal = dyn_cast<ConstantValue>(instr->getRHS())) {
    printArmInstr("mov", {"r2", getImme(constVal)});
  } else {
    printArmInstr("ldr", {"r2", getStackOper(instr->getRHS())});
  }
  printArmInstr("cmp", {"r1", "r2"});
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
