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

  struct NaiveAllocater {
    int intCounter = 0;
    int floatCounter = 0;
    // ARMv7 limits
    static constexpr int kMaxIntReg = 13; // remaining 3 for sp, lr, pc
    static constexpr int kMaxFloatReg = 16;

    std::string allocReg(Value *val) {
      if (val->getType()->isFloatTy()) {
        if (floatCounter < kMaxFloatReg) {
          return "s" + std::to_string(floatCounter++);
        } else {
          olc_unreachable("Reg Limit Exceeded");
        }
      } else {
        if (intCounter < kMaxIntReg) {
          return "r" + std::to_string(intCounter++);
        } else {
          olc_unreachable("Reg Limit Exceeded");
        }
      }
    }

    void reset() {
      intCounter = 0;
      floatCounter = 0;
    }
  } regAlloc;

  void loadToSpecificReg(std::string reg, Value *val) {
    if (auto *constVal = dyn_cast<ConstantValue>(val)) {
      printArmInstr("mov", {reg, getImme(constVal)});
    } else {
      printArmInstr("ldr", {reg, getStackOper(val)});
    }
  }

  std::string loadToReg(Value *val) {
    auto reg = regAlloc.allocReg(val);
    loadToSpecificReg(reg, val);
    return reg;
  }

  void storeRegToMemorySlot(std::string reg, Value *val) {
    printArmInstr("str", {reg, getStackOper(val)});
  }
};

} // namespace olc
