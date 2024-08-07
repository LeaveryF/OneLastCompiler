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
    printGlobalData(global);
  }

  os << ".bss\n";
  for (auto &global : module->globals) {
    printGlobalBss(global);
  }

  os << ".text\n";
  for (auto &func : module->functions) {
    os << ".global " << func->fnName << '\n';
  }
  for (auto &func : module->functions) {
    printFunc(func);
  }
}

void ArmWriter::printGlobalData(GlobalVariable *global) {
  if (!global->getInitializer())
    return;

  os << global->getName() << ":\n";
  assert(!global->getAllocatedType()->isFloatTy() && "NYI");
  std::function<void(Constant *)> printConstData = [&](Constant *val) {
    assert(val && "Invalid initializer");
    if (auto *arr = dyn_cast<ConstantArray>(val)) {
      for (auto *elt : arr->values) {
        printConstData(elt);
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
  printConstData(global->getInitializer());
}

void ArmWriter::printGlobalBss(GlobalVariable *global) {
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

void ArmWriter::printFunc(Function *function) {
  if (function->isBuiltin)
    return;

  curFunction = function;
  os << function->fnName << ":\n";

  // 保护好参数寄存器，直到它们存入栈中
  std::vector<Reg> arg_regs;
  for (unsigned i = 0; i < 4 && i < function->args.size(); i++) {
    arg_regs.emplace_back(regAlloc.claimIntReg(i));
  }

  // 计算栈空间
  stackSize = 0;
  stackMap.clear();

  // 给函数内 call 指令的栈参数分配 stack slot
  // 后续在 Call CodeGen 中直接引用 [sp, #0] 开始的一段栈空间
  int callStackSize = 0;
  for (auto &bb : function->basicBlocks) {
    for (auto &instr : bb->instructions) {
      if (auto *callInst = dyn_cast<CallInst>(instr)) {
        callStackSize =
            std::max(int(callInst->getArgs().size()) - 4, callStackSize);
      }
    }
  }
  stackSize += callStackSize * 4;

  // 给本函数的寄存器参数分配 stack slot
  for (unsigned i = 0; i < 4 && i < function->args.size(); i++) {
    stackMap[function->args[i]] = stackSize;
    stackSize += 4;
  }

  // 给指令结果分配 stack slot
  for (auto *bb : function->basicBlocks) {
    for (auto *instr : bb->instructions) {
      if (instr->tag == Value::Tag::Load)
        continue;
      if (instr->tag >= Value::Tag::BeginBooleanOp &&
          instr->tag <= Value::Tag::EndBooleanOp) {
        // For all br use, do not allocate stack. The codegen is in BranchInst.
        bool allBrUse = std::all_of(
            instr->uses.begin(), instr->uses.end(),
            [](const auto &use) { return isa<BranchInst>(use.user); });
        if (allBrUse)
          continue;
      }
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
  // TODO: 使用别的方式平栈（算术平栈）
  printArmInstr("push", {"{r11, lr}"});
  printArmInstr("mov", {"r11", "sp"});
  if (stackSize >= 256) {
    // 使用一个一定不会与参数寄存器冲突的寄存器用于加载
    auto reg_size = regAlloc.allocIntReg();
    printArmInstr("ldr", {reg_size, "=" + std::to_string(stackSize)});
    printArmInstr("sub", {"sp", "sp", reg_size});
  } else {
    printArmInstr("sub", {"sp", "sp", "#" + std::to_string(stackSize)});
  }

  // 保存寄存器参数到栈
  for (unsigned i = 0; i < 4 && i < function->args.size(); i++) {
    storeRegToMemorySlot(arg_regs[i], function->args[i]);
  }
  arg_regs.clear();

  // 栈上参数已经被调用方分配，直接插入 stack slot
  int argsOffset = stackSize;
  for (unsigned i = 4; i < function->args.size(); i++) {
    stackMap[function->args[i]] = argsOffset;
    argsOffset += 4;
  }

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
    auto reg_lhs = regAlloc.claimIntReg(0);
    loadToSpecificReg(reg_lhs, instr->getOperand(0));
    auto reg_rhs = regAlloc.claimIntReg(1);
    loadToSpecificReg(reg_rhs, instr->getOperand(1));
    printArmInstr("bl", {"__aeabi_idiv"});
    storeRegToMemorySlot(reg_lhs, instr);
    break;
  }
  case Value::Tag::Mod: {
    auto reg_lhs = regAlloc.claimIntReg(0);
    loadToSpecificReg(reg_lhs, instr->getOperand(0));
    auto reg_rhs = regAlloc.claimIntReg(1);
    loadToSpecificReg(reg_rhs, instr->getOperand(1));
    printArmInstr("bl", {"__aeabi_idivmod"});
    // 假设idivmod将除法结果放在R0，模结果放在R1
    printArmInstr("mov", {reg_rhs, "r1"}); // 将模结果移动到目标寄存器
    storeRegToMemorySlot(reg_rhs, instr);
    break;
  }
  case Value::Tag::IntToFloat: {
    auto *i2fInst = cast<IntToFloatInst>(instr);
    auto reg = regAlloc.claimIntReg(0);
    printArmInstr("ldr", {reg, getStackOper(i2fInst)});
    auto freg = regAlloc.claimFloatReg(0);
    printArmInstr("vldr.32", {freg, "[" + reg.abiName() + "]"});
    printArmInstr("vcvt.f32.u32", {freg, freg});
    storeRegToMemorySlot(freg, instr);
    break;
  }
  case Value::Tag::FloatToInt: {
    auto *f2iInst = cast<FloatToIntInst>(instr);
    auto reg = regAlloc.claimIntReg(0);
    printArmInstr("ldr", {reg, getStackOper(f2iInst)});
    auto freg = regAlloc.claimFloatReg(0);
    printArmInstr("vldr.32", {freg, "[" + reg.abiName() + "]"});
    printArmInstr("vcvt.u32.f32", {freg, freg});
    storeRegToMemorySlot(freg, instr);
    break;
  }
  case Value::Tag::Lt:
  case Value::Tag::Le:
  case Value::Tag::Ge:
  case Value::Tag::Gt:
  case Value::Tag::Eq:
  case Value::Tag::Ne: {
    // For all br use, do nothing. The codegen is in BranchInst.
    bool allBrUse = std::all_of(
        instr->uses.begin(), instr->uses.end(),
        [](const auto &use) { return isa<BranchInst>(use.user); });
    if (allBrUse)
      break;
    auto *cmpInst = cast<BinaryInst>(instr);
    if (isNaiveLogicalOp(cmpInst)) {
      auto reg_lhs = loadToReg(cmpInst->getLHS());
      if (cmpInst->tag == Value::Tag::Ne) {
        // Value Ne 0, Binarization
        printArmInstr("cmp", {reg_lhs, "#0"});
        printArmInstr("movne", {reg_lhs, "#1"});
        storeRegToMemorySlot(reg_lhs, instr);
      } else if (cmpInst->tag == Value::Tag::Eq) {
        // Value Eq 0, Logical negation
        printArmInstr("clz", {reg_lhs, reg_lhs});
        printArmInstr("lsrs", {reg_lhs, reg_lhs, "#5"});
        storeRegToMemorySlot(reg_lhs, instr);
      } else {
        olc_unreachable("Invalid tag");
      }
    } else {
      auto reg_lhs = loadToReg(cmpInst->getLHS());
      auto reg_rhs = loadToReg(cmpInst->getRHS());
      printArmInstr("cmp", {reg_lhs, reg_rhs});
      printArmInstr("mov" + getCondTagStr(cmpInst->tag), {reg_lhs, "#1"});
      printArmInstr(
          "mov" + getCondTagStr(getNotCond(cmpInst->tag)), {reg_lhs, "#0"});
      storeRegToMemorySlot(reg_lhs, instr);
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
    if (retInst->getNumOperands() == 1) {
      Reg reg_ret = retInst->getReturnValue()->getType()->isIntegerTy()
                        ? regAlloc.claimIntReg(0)
                        : regAlloc.claimFloatReg(0);
      assignToSpecificReg(reg_ret, retInst->getReturnValue());
    }
    printArmInstr("mov", {"sp", "r11"});
    printArmInstr("pop", {"{r11, lr}"});
    printArmInstr("bx", {"lr"});
    break;
  }
  case Value::Tag::Call: {
    auto *callInst = cast<CallInst>(instr);
    std::vector<Reg> callRegs;
    unsigned numRegs = std::clamp<unsigned>(callInst->getArgs().size(), 1, 4);
    for (unsigned i = 0; i < numRegs; i++)
      callRegs.emplace_back(regAlloc.claimIntReg(i));

    // TODO: consider float
    // 寄存器入参
    for (unsigned i = 0; i < 4 && i < callInst->getArgs().size(); i++) {
      assignToSpecificReg(callRegs[i], callInst->getArgs()[i]);
    }
    int argsOffset = 0;
    for (unsigned i = 4; i < callInst->getArgs().size(); i++) {
      auto reg_arg = loadToReg(callInst->getArgs()[i]);
      // 入参压栈
      printArmInstr(
          "str", {reg_arg, "[sp, #" + std::to_string(argsOffset) + "]"});
      argsOffset += 4;
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
