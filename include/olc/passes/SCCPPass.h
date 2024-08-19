#pragma once

#include <olc/ir/IR.h>
#include <olc/passes/Pass.h>

#include <map>
#include <set>

namespace olc {

struct ValueState {
  enum State { BOT, CONST, TOP };
  State state;
  ConstantValue *value;
  bool isbot() const { return state == BOT; }
  bool isconst() const { return state == CONST; }
  bool istop() const { return state == TOP; }
  void operator^=(const ValueState &rhs) {
    if (rhs.state < state) {
      state = rhs.state;
      value = rhs.value;
    } else if (rhs.state == state && state == CONST) {
      if (value->isInt()) {
        int x = value->getInt();
        int y = rhs.value->getInt();
        if (x != y) {
          state = BOT;
          value = nullptr;
        }
      } else {
        float x = value->getFloat();
        float y = rhs.value->getFloat();
        if (x != y) {
          state = BOT;
          value = nullptr;
        }
      }
    }
  }
};

class StateMap {
public:
  void clear() { map.clear(); }

private:
  std::map<Value *, ValueState> map;
};

class SCCPPass : public FunctionPass {
public:
  SCCPPass() : FunctionPass(&ID) {}

  bool runOnFunction(Function &function) override {
    //
    return true;
  }

  std::string getName() const override { return "SCCPPass"; }

private:
  StateMap stateMap;
  std::set<std::pair<BasicBlock *, BasicBlock *>> marked;
  std::vector<std::pair<BasicBlock *, Instruction *>> &worklist;
  std::vector<Instruction *> &ssa_worklist;

private:
  static const void *ID;
};

const void *SCCPPass::ID = reinterpret_cast<void *>(0x08191034);

class InstructionVisitor {
public:
  InstructionVisitor(
      SCCPPass &sccp, StateMap &stateMap,
      std::vector<std::pair<BasicBlock *, Instruction *>> &worklist,
      std::vector<Instruction *> &ssa_worklist)
      : sccp(sccp), stateMap(stateMap), worklist(worklist),
        ssa_worklist(ssa_worklist) {}
  void visit(Instruction *inst) {
    //
  }

private:
  void visit_phi(PhiInst *inst) {
    //
  }
  void visit_br(BranchInst *inst) {
    //
  }
  void visit_foldable(Instruction *inst) {
    //
  }

  SCCPPass &sccp;
  StateMap &stateMap;
  std::vector<std::pair<BasicBlock *, Instruction *>> &worklist;
  std::vector<Instruction *> &ssa_worklist;
  Instruction *inst_;
  BasicBlock *bb;
  ValueState prev_status;
  ValueState cur_status;
};
} // namespace olc
