#include <olc/backend/Liveness.h>

#include <map>
#include <stack>

namespace olc {

// Calc basic block liveness
LivenessBlockInfo::LivenessBlockInfo(BasicBlock *block) : block(block) {
  auto gatherOutValues = [&](Value *inst) {
    for (auto &&[user, idx] : inst->uses) {
      // is it always instruction?
      auto instUser = cast<Instruction>(user);
      if (instUser->parent != block) {
        outValues.insert(inst);
        break;
      }
    }
  };

  for (auto inst : block->instructions) {
    gatherOutValues(inst);
    if (inst->isDefVar())
      defValues.insert(inst);
    for (auto &&op : inst->operands) {
      useValues.insert(op);
    }
  }

  set_subtract(useValues, defValues);
}

// in = use U out \ def
bool LivenessBlockInfo::updateLiveIn() {
  ValueSetT newInValues = useValues;
  set_union(newInValues, outValues);
  set_subtract(newInValues, defValues);
  bool changed = newInValues.size() != inValues.size();
  inValues = std::move(newInValues);
  return changed;
}

// out = U_{succ} in_{succ}
void LivenessBlockInfo::updateLiveOut(BlockBuilderMapT const &infoMap) {
  for (auto succ : block->successors) {
    set_union(outValues, infoMap.at(succ).inValues);
  }
}

void InstOrderingManager::runOnFunction(Function *func) {
  std::stack<BasicBlock *> worklist;
  std::map<BasicBlock *, bool> visited;
  worklist.push(func->getEntryBlock());
  while (!worklist.empty()) {
    BasicBlock *block = worklist.top();
    worklist.pop();
    if (visited[block])
      continue;
    visited[block] = true;
    runOnBlock(block);
    for (auto succ : block->successors) {
      worklist.push(succ);
    }
  }
}

void InstOrderingManager::runOnBlock(BasicBlock *block) {
  blockOrder.push_back(block);

  for (auto inst : block->instructions) {
    auto count = instIDMap.size();
    instIDMap[inst] = 2 * count;
    idValueMap[count] = inst;
  }
}

void LivenessAnalysis::runOnFunction(Function *func) {
  instOrdering.runOnFunction(func);
  this->func = func;
  buildBlockInfoMap();
  calcLiveIntervals();
}

void LivenessAnalysis::buildBlockInfoMap() {
  std::vector<BasicBlock *> worklist;
  std::map<BasicBlock *, bool> present;

  for (auto block : instOrdering.blockOrder) {
    auto &blockInfo = blockInfoMap.try_emplace(block, block).first->second;
    if (blockInfo.updateLiveIn()) {
      for (auto pred : block->predecessors) {
        if (!present[pred]) {
          worklist.push_back(pred);
          present[pred] = true;
        }
      }
    }
  }

  while (!worklist.empty()) {
    auto block = worklist.back();
    worklist.pop_back();
    present[block] = false;
    auto &blockInfo = blockInfoMap.at(block);
    blockInfo.updateLiveOut(blockInfoMap);
    if (blockInfo.updateLiveIn()) {
      for (auto pred : block->predecessors) {
        if (!present[pred]) {
          worklist.push_back(pred);
          present[pred] = true;
        }
      }
    }
  }
}

void LivenessAnalysis::calcLiveIntervals() {
  auto inPoint = [&](Instruction *inst) {
    return instOrdering.instIDMap.at(inst);
  };
  auto outPoint = [&](Instruction *inst) {
    return instOrdering.instIDMap.at(inst) + 1;
  };

  // Handle arguments
  for (auto *arg : func->args) {
    updateInterval(arg, 0);
  }

  for (auto blockIt = instOrdering.blockOrder.rbegin();
       blockIt != instOrdering.blockOrder.rend(); ++blockIt) {
    auto block = *blockIt;
    auto &blockInfo = blockInfoMap.at(block);
    for (auto *inst : block->instructions) {
      assert(!inst->isPHI() && "NYI");

      // def
      if (inst->isDefVar())
        updateInterval(inst, outPoint(inst));

      // use
      for (auto &&op : inst->operands) {
        if (op->isDefVar())
          updateInterval(op, inPoint(inst));
      }
    }
  }
}

} // namespace olc
