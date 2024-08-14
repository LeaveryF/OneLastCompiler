#pragma once

#include <olc/backend/Liveness.h>
#include <olc/backend/MachineIR.h>

namespace olc {

struct LivePair {
  AsmReg *var;
  InstID start, end;

  LivePair(AsmReg *var, LiveIntervalT intv)
      : var(var), start(intv.first), end(intv.second) {}

public:
  struct StartAscend {
    bool operator()(const LivePair &a, const LivePair &b) const {
      return a.start < b.start;
    }
  };

  struct EndAscend {
    bool operator()(const LivePair &a, const LivePair &b) const {
      return a.end < b.end;
    }
  };
};

struct LinearScan {

  AsmFunc *func;
  std::set<LivePair, LivePair::StartAscend> scanningIntervals;
  std::set<LivePair, LivePair::EndAscend> activeIntervals;
  // no entry means spilled out
  std::map<AsmReg *, PReg *> regMap;
  std::set<PReg *> freeIntRegs, freeFloatRegs;

  void initRegs() {
    for (int i = 0; i < 13; i++)
      freeIntRegs.emplace(AsmReg::makePReg(AsmType::I32, i));
    for (int i = 0; i < 32; i++)
      freeFloatRegs.emplace(AsmReg::makePReg(AsmType::F32, i));
  }

  void constructIntervals() {
    LivenessAnalysis analysis;
    analysis.runOnFunction(func);
    auto &liveness = analysis.liveness;

    std::map<AsmReg *, std::pair<InstID, InstID>> activeIntervals;

    auto updateInterval = [&](AsmReg *reg, InstID i) {
      if (activeIntervals.count(reg) == 0) {
        activeIntervals[reg] = {i, i};
      } else {
        auto &interval = activeIntervals[reg];
        if (i < interval.first)
          interval.first = i;
        if (i > interval.second)
          interval.second = i;
      }
    };

    for (InstID i = 0; i < liveness.size(); ++i) {
      for (auto &&reg : liveness[i]) {
        updateInterval(reg, i);
      }
    }

    for (auto &&[reg, intv] : activeIntervals) {
      scanningIntervals.emplace(reg, intv);
    }
  }

  void runOnFunction(AsmFunc *func) {
    this->func = func;

    initRegs();
    constructIntervals();

    for (auto &intv : scanningIntervals) {
      expireOldIntervals(intv.start);
      if (!tryAllocateReg(intv)) {
        spillAtInterval(intv);
      }
    }
  }

  void expireOldIntervals(InstID curInst) {
    for (auto it = activeIntervals.begin(); it != activeIntervals.end();) {
      if (it->end < curInst) {
        auto *preg = regMap.at(it->var);
        if (preg->type == AsmType::F32) {
          freeFloatRegs.insert(preg);
        } else {
          freeIntRegs.insert(preg);
        }
        it = activeIntervals.erase(it);
      } else {
        break;
      }
    }
  }

  void spillAtInterval(LivePair const &intv) {
    auto spill = *activeIntervals.rbegin();
    if (spill.end > intv.end) {
      auto preg = regMap.at(spill.var);
      regMap.erase(spill.var);
      regMap[intv.var] = preg;
      activeIntervals.erase(spill);
      activeIntervals.insert(intv);
    }
  }

  bool tryAllocateReg(LivePair const &intv) {

    // check if the preg is already allocated, or spill now
    if (auto *preg = dyn_cast<PReg>(intv.var)) {
      if (preg->type == AsmType::F32) {
        if (freeFloatRegs.count(preg)) {
          freeFloatRegs.erase(preg);
          return true;
        } else {
          return false;
        }
      } else {
        // ignore special regs
        if (preg->id >= 13) {
          return true;
        }
        if (freeIntRegs.count(preg)) {
          freeIntRegs.erase(preg);
          return true;
        } else {
          return false;
        }
      }
    }

    if (intv.var->type == AsmType::F32) {
      if (freeFloatRegs.empty())
        return false;
      auto *reg = *freeFloatRegs.begin();
      freeFloatRegs.erase(freeFloatRegs.begin());
      regMap[intv.var] = reg;
    } else {
      if (freeIntRegs.empty())
        return false;
      auto *reg = *freeIntRegs.begin();
      freeIntRegs.erase(freeIntRegs.begin());
      regMap[intv.var] = reg;
    }
    activeIntervals.insert(intv);
    return true;
  }
};

} // namespace olc
