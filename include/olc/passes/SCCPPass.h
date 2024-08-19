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

class SCCPPass : public FunctionPass {
public:
  SCCPPass() : FunctionPass(&ID) {}

  bool runOnFunction(Function &function) override {
    if (function.isBuiltin)
      return false;
    bool modified = false;

    auto *instVisitor = new InstructionVisitor();
    worklist.emplace_back(nullptr, function.getEntryBlock());
    for (auto &bb : function.getBasicBlocks())
      for (auto &inst : bb->instructions)
        stateMap[bb] = ValueState::State::TOP;

    unsigned i = 0, j = 0;
    while (i < worklist.size() || j < ssa_worklist.size()) {
      while (i < worklist.size()) {
        auto &item = worklist[i++];
        if (marked.find(item) != marked.end())
          continue;
        marked.insert(item);
        auto &[preBB, curBB] = item;

        for (auto &inst : curBB->instructions) {
          instVisitor->visit(inst);
        }
      }
      while (j < ssa_worklist.size()) {
        auto *inst = ssa_worklist[j++];
        auto *curBB = inst->parent;

        for (auto &preBB : curBB->predecessors) {
          if (marked.find({preBB, curBB}) != marked.end()) {
            instVisitor->visit(inst);
            break;
          }
        }
      }
    }
    return true;
  }

  std::string getName() const override { return "SCCPPass"; }

private:
  std::map<Value *, ValueState::State> stateMap;
  std::set<std::pair<BasicBlock *, BasicBlock *>> marked;
  std::vector<std::pair<BasicBlock *, BasicBlock *>> worklist;
  std::vector<Instruction *> ssa_worklist;

private:
  static const void *ID;
};

const void *SCCPPass::ID = reinterpret_cast<void *>(0x08191034);

class InstructionVisitor {
public:
  InstructionVisitor(
      SCCPPass &sccp, std::map<Value *, ValueState::State> &stateMap,
      std::vector<std::pair<BasicBlock *, BasicBlock *>> &worklist,
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
  std::map<Value *, ValueState::State> &stateMap;
  std::vector<std::pair<BasicBlock *, BasicBlock *>> &worklist;
  std::vector<Instruction *> &ssa_worklist;

  Instruction *inst_;
  BasicBlock *bb;
  ValueState prev_status;
  ValueState cur_status;
};
} // namespace olc
