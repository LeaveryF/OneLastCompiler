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
  ConstantValue *value = nullptr;

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

    cfg_worklist.emplace_back(nullptr, function.getEntryBlock());
    for (auto &bb : function.getBasicBlocks())
      for (auto &inst : bb->instructions)
        stateMap[bb] = {ValueState::State::TOP};

    unsigned i = 0, j = 0;
    while (i < cfg_worklist.size() || j < ssa_worklist.size()) {
      while (i < cfg_worklist.size()) {
        auto &item = cfg_worklist[i++];
        if (marked.find(item) != marked.end())
          continue;
        marked.insert(item);
        auto &[preBB, curBB] = item;

        for (auto &inst : curBB->instructions) {
          visitInst(inst);
        }
      }
      while (j < ssa_worklist.size()) {
        auto *inst = ssa_worklist[j++];
        auto *curBB = inst->parent;

        for (auto &preBB : curBB->predecessors) {
          if (marked.find({preBB, curBB}) != marked.end()) {
            visitInst(inst);
            break;
          }
        }
      }
    }
    return true;
  }

  std::string getName() const override { return "SCCPPass"; }

private:
  std::map<Value *, ValueState> stateMap;
  std::set<std::pair<BasicBlock *, BasicBlock *>> marked;
  std::vector<std::pair<BasicBlock *, BasicBlock *>> cfg_worklist;
  std::vector<Instruction *> ssa_worklist;

  Instruction *inst;
  BasicBlock *bb;
  ValueState prev_state;
  ValueState cur_state;

  ValueState getValueState(Value *inst) {
    if (isa<ConstantValue>(inst)) {
      prev_state = {ValueState::State::CONST, cast<ConstantValue>(inst)};
    } else {
      prev_state = stateMap.at(inst);
    }
  }

  void visitInst(Instruction *inst) {
    this->inst = inst;
    bb = inst->parent;
    prev_state = getValueState(inst);
    cur_state = prev_state;

    if (auto *phiInst = dyn_cast<PhiInst>(inst)) {
      const int phi_size = phiInst->getNumOperands() / 2;
      for (int i = 0; i < phi_size; i++) {
        auto *pre_bb = cast<BasicBlock>(phiInst->getOperand(i * 2 + 1));
        if (marked.count({pre_bb, bb})) {
          auto *op = phiInst->getOperand(i * 2);
          auto opState = getValueState(op);
          cur_state ^= opState;
        }
      }
    } else if (auto *brInst = dyn_cast<BranchInst>(inst)) {
      if (!brInst->isConditional()) {
        auto target = brInst->getCondition();
        cfg_worklist.emplace_back(bb, target);
        return;
      }
      auto *trueBlock = brInst->getTrueBlock();
      auto *falseBlock = brInst->getFalseBlock();
      auto *const_cond = dyn_cast<ConstantValue>(brInst->getCondition());
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
    } else if (auto *binInst = dyn_cast<BinaryInst>(inst)) {
      if (auto lhs = dyn_cast<ConstantValue>(binInst->getLHS())) {
        if (auto rhs = dyn_cast<ConstantValue>(binInst->getRHS())) {
          ConstantValue *result = ConstFold(binInst, lhs, rhs);
          cur_state = {ValueState::CONST, result};
          return;
        }
      }
      cur_state = {ValueState::TOP};
      int num_operands = binInst->getNumOperands();
      for (int i = 0; i < num_operands; i++) {
        auto *op = binInst->getOperand(i);
        if (getValueState(op).isbot()) {
          cur_state = {ValueState::BOT};
          return;
        }
      }
    }
  }

private:
  static const void *ID;
};

const void *SCCPPass::ID = reinterpret_cast<void *>(0x08191034);

} // namespace olc
