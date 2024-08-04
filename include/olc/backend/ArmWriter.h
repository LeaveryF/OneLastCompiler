#include <olc/ir/IR.h>

#include <iostream>
#include <unordered_map>

namespace olc {

class ArmWriter {
  std::ostream &os;
  std::unordered_map<Value *, int> stackMap;
  std::unordered_map<BasicBlock *, int> labelMap;
  int stackSize;
  int paramCnt;
  int curReg;

  std::string getCondTagStr(Value::Tag tag) {
    switch (tag) {
    case Value::Tag::Eq:
      return "eq";
    case Value::Tag::Ne:
      return "ne";
    case Value::Tag::Lt:
      return "lt";
    case Value::Tag::Le:
      return "le";
    case Value::Tag::Gt:
      return "gt";
    case Value::Tag::Ge:
      return "ge";
    default:
      olc_unreachable("Invalid tag");
    }
  }

public:
  ArmWriter(std::ostream &os) : os(os) {}

  void printModule(Module *);
  void printGlobal(GlobalVariable *);
  void printFunc(Function *);
  void printBasicBlock(BasicBlock *);
  void printInstr(std::list<Instruction *>::iterator &);
  void printArmInstr(
      const std::string &op, const std::vector<std::string> &operands);
  void printBinInstr(const std::string &op, Instruction *instr);
  void printCmpInstr(BinaryInst *instr);
  std::string getStackOper(Value *val);
  std::string getImme(ConstantValue *val);
  std::string getReg();
  std::string getLabel(BasicBlock *bb);
  // dispatch to the corresponding get- functions above
  std::string getFromValue(Value *val) {
    if (auto *cv = dyn_cast<ConstantValue>(val))
      return getImme(cv);
    assert(isa<Instruction>(val) && "NYI");
    // else, use memory slot
    return getStackOper(val);
  }
};

} // namespace olc
