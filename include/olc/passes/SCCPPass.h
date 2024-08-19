#pragma once

#include <olc/ir/IR.h>
#include <olc/passes/ConstantFoldingPass.h>
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
  bool operator!=(const ValueState &rhs) const {
    if (state != rhs.state) {
      return true;
    }
    if (state == CONST) {
      if (value->isInt()) {
        int l = value->isInt();
        int r = rhs.value->getInt();
        return l != r;
      } else {
        float l = value->getFloat();
        float r = rhs.value->getFloat();
        return l != r;
      }
    }
    return false;
  }
};

class StateMap {
public:
  ValueState &operator[](Value *value) { return map[value]; }
  ValueState get(Value *value) const {
    if (auto constant = dyn_cast<ConstantValue>(value)) {
      return ValueState{ValueState::CONST, constant};
    }
    return map.at(value);
  }
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
  std::vector<std::pair<BasicBlock *, Instruction *>> cfg_worklist;
  std::vector<Instruction *> ssa_worklist;

  Instruction *inst;
  BasicBlock *bb;
  ValueState prev_state;
  ValueState cur_state;

  void visit(Instruction *inst) {
    this->inst = inst;
    bb = inst->parent;
    prev_state = stateMap.get(inst);
    cur_state = prev_state;

    if (inst->isPHI()) {
      visit_phi(cast<PhiInst>(inst));
    } else if (isa<BranchInst>(inst)) {
      visit_br(cast<BranchInst>(inst));
    } else if (isa<BinaryInst>(inst)) {
      visit_foldable(cast<BinaryInst>(inst));
    } else {
      cur_state = {ValueState::BOT};
    }
    if (cur_state != prev_state) {
      stateMap[inst] = cur_state;
      for (auto use : inst->uses) {
        auto *user = dyn_cast<Instruction>(use.user);
        ssa_worklist.push_back(user);
      }
    }
  }
  void visit_phi(PhiInst *inst) {
    const int phi_size = inst->getNumOperands() / 2;
    for (int i = 0; i < phi_size; i++) {
      auto *pre_bb = cast<BasicBlock>(inst->getOperand(i * 2 + 1));
      if (marked.count({pre_bb, bb})) {
        auto *op = inst->getOperand(i * 2);
        auto opState = stateMap.get(op);
        cur_state ^= opState;
      }
    }
  }
  void visit_br(BranchInst *inst) {
    if (!inst->isConditional()) {
      auto target = inst->getCondition();
      cfg_worklist.emplace_back(bb, target);
      return;
    }
    auto *trueBlock = inst->getTrueBlock();
    auto *falseBlock = inst->getFalseBlock();
    auto *const_cond = dyn_cast<ConstantValue>(inst->getCondition());
    if (const_cond) {
      if (const_cond->getInt() == 1) {
        cfg_worklist.emplace_back(bb, trueBlock);
      } else {
        cfg_worklist.emplace_back(bb, falseBlock);
      }
    } else {
      cfg_worklist.emplace_back(bb, trueBlock);
      cfg_worklist.emplace_back(bb, falseBlock);
    }
  }
  void visit_foldable(BinaryInst *inst) {
    if (auto lhs = dyn_cast<ConstantValue>(inst->getLHS())) {
      if (auto rhs = dyn_cast<ConstantValue>(inst->getRHS())) {
        ConstantValue *result = ConstFold(inst, lhs, rhs);
        cur_state = {ValueState::CONST, result};
        return;
      }
    }
    cur_state = {ValueState::TOP};
    int num_operands = inst->getNumOperands();
    for (int i = 0; i < num_operands; i++) {
      auto *op = inst->getOperand(i);
      if (stateMap.get(op).isbot()) {
        cur_state = {ValueState::BOT};
        return;
      }
    }
  }

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

private:
  SCCPPass &sccp;
  StateMap &stateMap;
  std::vector<std::pair<BasicBlock *, Instruction *>> &worklist;
  std::vector<Instruction *> &ssa_worklist;
  Instruction *inst;
  BasicBlock *bb;
  ValueState prev_state;
  ValueState cur_state;
};
} // namespace olc
