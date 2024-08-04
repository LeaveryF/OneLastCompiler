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

public:
  ArmWriter(std::ostream &os) : os(os) {}

  void printModule(Module *);
  void printGlobal(GlobalVariable *);
  void printFunc(Function *);
  void printBasicBlock(BasicBlock *);
  void printInstr(Instruction *);
  void printArmInstr(
      const std::string &op, const std::vector<std::string> &operands);
  void printBinInstr(const std::string &op, Instruction *instr);
  void printCmpInstr(const std::string &op, Instruction *instr);
  std::string getStackOper(Value *val);
  std::string getImme(ConstantValue *val);
  std::string getReg();
  std::string getLabel(BasicBlock *bb);
};

} // namespace olc
