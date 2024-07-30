#include <olc/ir/AsmWriter.h>

#include <map>

namespace olc {

void AssemblyWriter::printModule(Module *module) {
  for (auto &global : module->globals) {
    printGlobal(global);
  }
  os << "\n";
  for (auto &func : module->functions) {
    printFunc(func);
    os << "\n";
  }
}

void AssemblyWriter::printGlobal(GlobalVariable *global) {
  os << "@" << global->getName() << " = global ";
  global->getAllocatedType()->print(os);
  os << ", ";
  if (auto *initializer = global->getInitializer())
    initializer->print(os);
  else
    os << "zeroinitializer";
  os << "\n";
}

void AssemblyWriter::printFunc(Function *function) {
  nameManager.reset();

  os << "define @" << function->fnName;

  // arguments
  os << "(";
  for (unsigned i = 0; i < function->args.size(); i++) {
    if (i > 0)
      os << ", ";
    function->args[i]->getType()->print(os);
    os << " %" << function->args[i]->argName;
  }

  os << ") -> ";
  function->getReturnType()->print(os);

  os << " {\n";
  if (function->isBuiltin)
    olc_unreachable("NYI");
  for (auto &bb : function->basicBlocks) {
    printBasicBlock(bb);
  }
  os << "}\n";
}

void AssemblyWriter::printBasicBlock(BasicBlock *basicBlock) {
  os << basicBlock->label << ":\n";
  if (!basicBlock->predecessors.empty()) {
    os << "; prev:";
    for (auto *pred : basicBlock->predecessors) {
      os << " " << pred->label;
    }
    os << "\n";
  }
  if (!basicBlock->successors.empty()) {
    os << "; next:";
    for (auto *succ : basicBlock->successors) {
      os << " " << succ->label;
    }
    os << "\n";
  }

  for (auto *instr : basicBlock->instructions) {
    assert(instr->getType() && "must have type");
    if (!instr->getType()->isVoidTy())
      nameManager.add(instr);
    printInstr(instr);
  }
}

constexpr char const *kInstTagToOpName[] = {
    "add",   "sub", "mul",  "div",    "mod", "lt",
    "le",    "ge",  "gt",   "eq",     "ne",  "and",
    "or",    "rsb", "br",   "jmp",    "ret", "getelementptr",
    "ld",    "st",  "call", "alloca", "phi", "memop",
    "memphi"};

void AssemblyWriter::printInstr(Instruction *instruction) {
  auto *opName = kInstTagToOpName
      [static_cast<int>(instruction->tag) -
       static_cast<int>(Value::Tag::BeginInst)];

  // indent for instructions
  os << "  ";
  if (!instruction->getType()->isVoidTy())
    os << "%" << nameManager[instruction] << " = ";

  os << opName;

  if (auto *instr = dyn_cast<AllocaInst>(instruction)) {
    os << " ";
    instr->getAllocatedType()->print(os);
  }

  for (unsigned i = 0; i < instruction->getNumOperands(); i++) {
    auto &op = instruction->operands[i];
    if (!isa<CallInst>(instruction)) {
      if (i > 0)
        os << ",";
      os << " ";
    } else {
      if (i > 1)
        os << ",";
      if (i != 1)
        os << " ";
    }
    if (auto *constVal = dyn_cast<Constant>(op)) {
      constVal->print(os);
    } else if (auto *instr = dyn_cast<Instruction>(op)) {
      os << "%" << nameManager[instr];
    } else if (auto *arg = dyn_cast<Argument>(op)) {
      os << "%" << arg->argName;
    } else if (auto *bb = dyn_cast<BasicBlock>(op)) {
      os << "label %" << bb->label;
    } else if (auto *func = dyn_cast<Function>(op)) {
      os << "@" << func->fnName;
      os << "(";
    } else {
      olc_unreachable("NYI");
    }
  }

  if (auto *instr = dyn_cast<CallInst>(instruction)) {
    os << ")";
  }

  os << "\n";
}
} // namespace olc
