#pragma once

#include <olc/ir/IR.h>
#include <olc/passes/Pass.h>

#include <algorithm>
#include <set>

namespace olc {

class Mem2RegPass : public FunctionPass {
public:
  Mem2RegPass() : FunctionPass(&ID) {}

  bool runOnFunction(Function &function) override {
    return true;
  }

  std::string getName() const override { return "Mem2RegPass"; }

private:
  static const void *ID;
};

const void *Mem2RegPass::ID = reinterpret_cast<void *>(0x29712683);

} // namespace olc
