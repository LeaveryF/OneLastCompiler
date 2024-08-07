#include <olc/ir/IR.h>

#include <iostream>
#include <set>
#include <unordered_map>
#include <sstream>

namespace olc {

class ArmWriter {
  std::ostream &os;
  std::unordered_map<Value *, int> stackMap;
  std::unordered_map<BasicBlock *, int> labelMap;
  Function *curFunction = nullptr;
  int stackSize;
  int floatCnt = 0;

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

  Value::Tag getNotCond(Value::Tag tag) {
    switch (tag) {
    case Value::Tag::Eq:
      return Value::Tag::Ne;
    case Value::Tag::Ne:
      return Value::Tag::Eq;
    case Value::Tag::Lt:
      return Value::Tag::Ge;
    case Value::Tag::Le:
      return Value::Tag::Gt;
    case Value::Tag::Gt:
      return Value::Tag::Le;
    case Value::Tag::Ge:
      return Value::Tag::Lt;
    default:
      olc_unreachable("Invalid tag");
    }
  }

  bool isNaiveLogicalOp(Instruction *instr) {
    auto *cmpInst = dyn_cast<BinaryInst>(instr);
    if (!cmpInst ||
        (cmpInst->tag != Value::Tag::Ne && cmpInst->tag != Value::Tag::Eq))
      return false;
    auto *rhs = dyn_cast<ConstantValue>(cmpInst->getRHS());
    if (!rhs || !rhs->isInt() || rhs->getInt() != 0)
      return false;
    return true;
  }

public:
  ArmWriter(std::ostream &os) : os(os) {}

  void printModule(Module *);
  void printGlobalData(GlobalVariable *);
  void printGlobalBss(GlobalVariable *);
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

  struct NaiveAllocater;
  // RAII helper for reg alloc
  struct Reg {
    bool isFloat;
    int id;
    NaiveAllocater *alloc;
    std::string abiName() const {
      assert(id >= 0 && "Invalid reg!");
      if (isFloat) {
        return "s" + std::to_string(id);
      } else {
        return "r" + std::to_string(id);
      }
    }
    operator std::string() const { return abiName(); }
    Reg(bool isFloat, int id, NaiveAllocater *alloc)
        : isFloat(isFloat), id(id), alloc(alloc) {}
    ~Reg();
    Reg(const Reg &) = delete;
    Reg &operator=(const Reg &) = delete;
    Reg(Reg &&);
    Reg &operator=(Reg &&);
  };

  struct NaiveAllocater {
    std::set<int> intRegs, fltRegs;

    NaiveAllocater() { reset(); }

    Reg allocIntReg() {
      if (intRegs.size()) {
        int allocated = *intRegs.begin();
        intRegs.erase(intRegs.begin());
        return Reg{false, allocated, this};
      } else {
        olc_unreachable("Reg Limit Exceeded");
      }
    }

    Reg allocFloatReg() {
      if (fltRegs.size()) {
        int allocated = *fltRegs.begin();
        fltRegs.erase(fltRegs.begin());
        return Reg{true, allocated, this};
      } else {
        olc_unreachable("Reg Limit Exceeded");
      }
    }

    Reg claimIntReg(int reg) {
      if (auto it = intRegs.find(reg); it != intRegs.end()) {
        intRegs.erase(it);
      } else {
        olc_unreachable("Reg conflict");
      }
      return Reg{false, reg, this};
    }

    Reg claimFloatReg(int reg) {
      if (auto it = fltRegs.find(reg); it != fltRegs.end()) {
        fltRegs.erase(it);
      } else {
        olc_unreachable("Reg conflict");
      }
      return Reg{true, reg, this};
    }

    Reg allocReg(Value *val) {
      if (val->getType()->isFloatTy()) {
        return allocFloatReg();
      } else {
        return allocIntReg();
      }
    }

    void reset() {
      intRegs.clear();
      fltRegs.clear();
      for (int i = 0; i <= 12; ++i) {
        intRegs.insert(i);
      }
      for (int i = 0; i < 32; ++i) {
        fltRegs.insert(i);
      }
    }
  } regAlloc;

  void loadToSpecificReg(Reg const &reg, Value *val) {
    if (auto *constVal = dyn_cast<ConstantValue>(val)) {
      if (constVal->isInt()) {
        printArmInstr("ldr", {reg, "=" + std::to_string(constVal->getInt())});
      } else {
        // get hex of float
        union {
          float f;
          uint32_t i;
        } u;
        u.f = constVal->getFloat();
        std::stringstream ss;
        ss << std::hex << u.i;
        auto reg_int = regAlloc.allocIntReg();
        printArmInstr("ldr", {reg_int, "=0x" + ss.str()});
        printArmInstr("vmov.f32", {reg, reg_int});
      }
    } else {
      if (auto *ld = dyn_cast<LoadInst>(val)) {
        val = ld->getPointer();
        if (auto *gv = dyn_cast<GlobalVariable>(val)) {
          // printArmInstr("ldr", {reg, "=" + gv->getName()});
          printArmInstr("movw", {reg, "#:lower16:" + gv->getName()});
          printArmInstr("movt", {reg, "#:upper16:" + gv->getName()});
          printArmInstr("ldr", {reg, "[" + reg.abiName() + "]"});
        } else if (auto *alloca = dyn_cast<AllocaInst>(val)) {
          printArmInstr("ldr", {reg, getStackOper(val)});
        } else { // If non-static address, use memory slot
          // Load from memory slot
          printArmInstr("ldr", {reg, getStackOper(val)});
          // Load from the loaded address
          printArmInstr("ldr", {reg, "[" + reg.abiName() + "]"});
        }
      } else {
        if (auto *gv = dyn_cast<GlobalVariable>(val)) {
          // printArmInstr("ldr", {reg, "=" + gv->getName()});
          printArmInstr("movw", {reg, "#:lower16:" + gv->getName()});
          printArmInstr("movt", {reg, "#:upper16:" + gv->getName()});
        } else if (auto *alloca = dyn_cast<AllocaInst>(val)) {
          printArmInstr(
              "add", {reg, "sp", "#" + std::to_string(stackMap[val])});
        } else { // If non-static address, use memory slot
          printArmInstr("ldr", {reg, getStackOper(val)});
        }
      }
    }
  }

  Reg loadToReg(Value *val) {
    auto reg = regAlloc.allocReg(val);
    loadToSpecificReg(reg, val);
    return reg;
  }

  void assignToSpecificReg(const Reg &reg, Value *val) {
    if (auto *arg = dyn_cast<Argument>(val)) {
      if (int argNo = curFunction->getArgNo(arg); argNo < 4) {
        assert(!arg->getType()->isFloatTy() && "NYI");
        printArmInstr("mov", {reg, regAlloc.claimIntReg(argNo)});
        return;
      }
    }
    // Otherwise, the value has a memory slot.
    loadToSpecificReg(reg, val);
  }

  void storeRegToMemorySlot(const Reg &reg, Value *val) {
    assert(!isa<AllocaInst>(val) && "Alloca has no memory slot.");
    printArmInstr(reg.isFloat ? "vstr.32" : "str", {reg, getStackOper(val)});
  }

  void storeRegToAddress(const Reg &reg, Value *ptr) {
    if (auto *alloca = dyn_cast<AllocaInst>(ptr)) {
      printArmInstr("str", {reg, getStackOper(ptr)});
    } else {
      auto reg_ptr = loadToReg(ptr);
      printArmInstr("str", {reg, "[" + reg_ptr.abiName() + "]"});
    }
  }
};

} // namespace olc
