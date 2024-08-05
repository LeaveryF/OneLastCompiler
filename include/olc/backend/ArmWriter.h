#include <olc/ir/IR.h>

#include <iostream>
#include <unordered_map>

namespace olc {

class ArmWriter {
  std::ostream &os;
  std::unordered_map<Value *, int> stackMap;
  std::unordered_map<BasicBlock *, int> labelMap;
  Function *curFunction = nullptr;
  int stackSize;

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
      if (auto *ld = dyn_cast<LoadInst>(val)) {
        val = ld->getPointer();
        if (auto *gv = dyn_cast<GlobalVariable>(val)) {
          printArmInstr("ldr", {reg, "=" + gv->getName()});
          printArmInstr("ldr", {reg, "[" + reg + "]"});
        } else if (auto *alloca = dyn_cast<AllocaInst>(val)) {
          printArmInstr("ldr", {reg, getStackOper(val)});
        } else { // If non-static address, use memory slot
          // Load from memory slot
          printArmInstr("ldr", {reg, getStackOper(val)});
          // Load from the loaded address
          printArmInstr("ldr", {reg, "[" + reg + "]"});
        }
      } else {
        if (auto *gv = dyn_cast<GlobalVariable>(val)) {
          printArmInstr("ldr", {reg, "=" + gv->getName()});
        } else if (auto *alloca = dyn_cast<AllocaInst>(val)) {
          printArmInstr(
              "add", {reg, "sp", "#" + std::to_string(stackMap[val])});
        } else { // If non-static address, use memory slot
          printArmInstr("ldr", {reg, getStackOper(val)});
        }
      }
    }
  }

  std::string loadToReg(Value *val) {
    if (auto *arg = dyn_cast<Argument>(val)) {
      if (int argNo = curFunction->getArgNo(arg); argNo < 4) {
        return "r" + std::to_string(argNo);
      }
      // Otherwise, there should be a memory slot allocated for it.
    }
    auto reg = regAlloc.allocReg(val);
    loadToSpecificReg(reg, val);
    return reg;
  }

  void assignToSpecificReg(std::string reg, Value *val) {
    if (auto *arg = dyn_cast<Argument>(val)) {
      if (int argNo = curFunction->getArgNo(arg); argNo < 4) {
        printArmInstr("mov", {reg, "r" + std::to_string(argNo)});
        return;
      }
    }
    // Otherwise, the value has a memory slot.
    loadToSpecificReg(reg, val);
  }

  void storeRegToMemorySlot(std::string reg, Value *val) {
    printArmInstr("str", {reg, getStackOper(val)});
  }
};

} // namespace olc
