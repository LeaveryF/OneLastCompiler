#include <olc/ir/IR.h>

#include <iostream>
#include <set>
#include <unordered_map>

namespace olc {
class ArmModule {
  std::vector<ArmFunction *> funcs;
  std::vector<GlobalVariable *> glob;
};
class ArmFunction {
  Function *func;
  std::vector<ArmBasicBlock *> bb;
};
class ArmBasicBlock {
  BasicBlock *bb;
  std::vector<ArmInstruction *> insts;
};
class ArmInstruction {
  Instruction *inst;
  ArmBasicBlock *bb;
  enum class Tag {
    // instructions
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Lt,
    Le,
    Ge,
    Gt,
    Eq,
    Ne,
    Branch,
    Jump,
    Return,
    GetElementPtr,
    Load,
    Store,
    Call,
    Alloca,
    Phi,
    IntToFloat, // 新增
    FloatToInt, // 新增

    // anchors
    BeginInst = Add,
    EndInst = FloatToInt,
    BeginBinOp = Add,
    EndBinOp = Ne,
    BeginBooleanOp = Lt,
    EndBooleanOp = Ne,
  } tag;
};
} // namespace olc