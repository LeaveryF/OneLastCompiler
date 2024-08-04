#pragma once

#include <olc/ir/IR.h>

#include <olc/Support.h>

#include <map>
#include <set>
#include <limits>

namespace olc {

struct LivenessBlockInfo;

using InstID = size_t;
using ValueSetT = std::set<Value *>;
using BlockBuilderMapT = std::map<BasicBlock *, LivenessBlockInfo>;
using LiveIntervalT = std::pair<InstID, InstID>;

struct LivenessBlockInfo {

  LivenessBlockInfo() = default;

  LivenessBlockInfo(BasicBlock *block);

  // in = use U out \ def
  bool updateLiveIn();

  // out = U_{succ} in_{succ}
  void updateLiveOut(BlockBuilderMapT const &infoMap);

  /// The current block.
  BasicBlock *block{nullptr};

  ValueSetT inValues;
  ValueSetT outValues;
  ValueSetT defValues;
  ValueSetT useValues;
};

struct InstOrderingManager {

  InstOrderingManager() = default;

  void runOnFunction(Function *func);
  void runOnBlock(BasicBlock *bb);

  std::vector<BasicBlock *> blockOrder;
  std::map<Value *, InstID> instIDMap;
  std::map<InstID, Value *> idValueMap;
};

struct LivenessAnalysis {
  LivenessAnalysis() = default;

  void runOnFunction(Function *func);

  InstOrderingManager instOrdering;
  BlockBuilderMapT blockInfoMap;
  std::map<Value *, LiveIntervalT> liveIntervals;

private:
  Function *func;
  void buildBlockInfoMap();
  void calcLiveIntervals();
  void updateInterval(Value *val, InstID id) {
    auto &&[iter, _] = liveIntervals.try_emplace(val, std::numeric_limits<InstID>::max(), 0);
    auto &interval = iter->second;
    interval.first = std::min(interval.first, id);
    interval.second = std::max(interval.second, id);
  }
};

} // namespace olc
