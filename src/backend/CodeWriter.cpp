#include "olc/backend/MachineIR.h"
#include <olc/backend/CodeWriter.h>

namespace olc {

void CodeWriter::printModule(AsmModule *module) {
  for (auto &global : module->globals) {
    printGlobal(global);
  }
  os << "\n";
  for (auto &func : module->funcs) {
    printFunc(func);
    os << "\n";
  }
}

void CodeWriter::printGlobal(GlobalVariable *global) {
  os << ".global " << global->getName() << "\n";
}

void CodeWriter::printFunc(AsmFunc *func) {
  if (func->isBuiltin) {
    return;
  } else {
    os << func->name << ":\n";
    for (auto &lable : func->labels) {
      printLabel(lable);
    }
  }
}

void CodeWriter::printLabel(AsmLabel *label) {
  os << label->name << ":\n";
  for (auto inst = label->Head; inst != nullptr; inst = inst->Next) {
    printInst(inst);
  }
}

std::string CodeWriter::to_string(AsmValue *value) {
  std::string res;
  if (auto *reg = dyn_cast<AsmReg>(value)) {
    if (auto *preg = dyn_cast<PReg>(reg)) {
      res = preg->abiName();
    } else if (auto *vreg = dyn_cast<VReg>(reg)) {
      res = "%" + std::to_string(vreg->id);
    }
  } else if (auto *imm = dyn_cast<AsmImm>(value)) {
    res = std::to_string(imm->hexValue);
  } else {
    olc_unreachable("Invalid asm value");
  }
  return res;
}

void CodeWriter::printInst(AsmInst *inst) {
  static std::vector<std::string> tags = {
      "add",    "sub",  "mul",  "div",   "mod",  "cmp",        "branch", "jump",
      "return", "move", "load", "store", "call", "loadglobal", "string"};

  std::string op = tags[(int)inst->tag];
  if (auto *binInst = dyn_cast<AsmBinaryInst>(inst)) {
    // printValue(binInst->lhs);
    // os << ", ";
    // printValue(binInst->rhs);
    // os << ", ";
    // printValue(binInst->dst);
    // os << "\n";
    printCodeInstr(
        op, {to_string(binInst->lhs), to_string(binInst->rhs),
             to_string(binInst->dst)});

  } else if (auto *cmpInst = dyn_cast<AsmCompareInst>(inst)) {
    printCodeInstr(op, {to_string(cmpInst->lhs), to_string(cmpInst->rhs)});

  } else if (auto *branchInst = dyn_cast<AsmBranchInst>(inst)) {
    static std::vector<std::string> condTags = {"al", "eq", "ne", "lt",
                                                "le", "ge", "gt"};
    std::string cond = "b";
    if (branchInst->pred != AsmPredicate::Al) {
      cond += condTags[(int)branchInst->pred];
    }
    printCodeInstr(cond, {cond + " ." + branchInst->trueTarget->name});
    printCodeInstr("b", {cond + " ." + branchInst->falseTarget->name});
  } else if (auto *jumpInst = dyn_cast<AsmJumpInst>(inst)) {
    printCodeInstr("b", {". " + jumpInst->target->name});
  } else if (auto *retInst = dyn_cast<AsmReturnInst>(inst)) {
    printCodeInstr(op, {});
  } else if (auto *moveInst = dyn_cast<AsmMoveInst>(inst)) {
    printCodeInstr(op, {to_string(moveInst->dst), to_string(moveInst->src)});
  } else if (auto *loadInst = dyn_cast<AsmLoadInst>(inst)) {
    printCodeInstr(op, {to_string(loadInst->dst), to_string(loadInst->addr)});
  } else if (auto *storeInst = dyn_cast<AsmStoreInst>(inst)) {
    printCodeInstr(op, {to_string(storeInst->src), to_string(storeInst->addr)});
  } else if (auto *callInst = dyn_cast<AsmCallInst>(inst)) {
    printCodeInstr(op, {callInst->callee});
  } else {
    os << "invalid instr here" << std::endl;
  }
}
} // namespace olc
