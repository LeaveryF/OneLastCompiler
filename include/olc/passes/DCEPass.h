#pragma once

#include <olc/ir/IR.h>
#include <olc/passes/Pass.h>
#include <set>

namespace olc {

class DeadCodeEliminationPass : public FunctionPass {
public:
  DeadCodeEliminationPass() : FunctionPass(&ID) {}

  bool runOnFunction(Function &function) override {
    std::set<Value *> liveValues;
    bool changed = false;

    // 逆向遍历基本块中的指令
    for (auto bbIter = function.basicBlocks.rbegin();
         bbIter != function.basicBlocks.rend(); ++bbIter) {
      auto &bb = **bbIter;
      for (auto instIter = bb.instructions.rbegin();
           instIter != bb.instructions.rend();) {
        Instruction *inst = *instIter;

        if (!isLive(inst, liveValues) && !hasSideEffect(inst)) {
          // 删除死代码
          instIter = std::list<Instruction *>::reverse_iterator(
              bb.instructions.erase(std::next(instIter).base()));
          delete inst;
          changed = true;
        } else {
          // 标记指令的操作数为活跃
          for (auto *operand : inst->operands) {
            liveValues.insert(operand);
          }
          ++instIter;
        }
      }
    }

    return changed;
  }

  std::string getName() const override { return "DeadCodeEliminationPass"; }

private:
  static const void *ID;

  bool isLive(Value *value, const std::set<Value *> &liveValues) const {
    return liveValues.find(value) != liveValues.end();
  }

  bool hasSideEffect(Instruction *inst) const {
    // 判断指令是否有副作用
    switch (inst->tag) {
    case Value::Tag::Store:
    case Value::Tag::Call:
    case Value::Tag::Return:
      return true;
    default:
      return false;
    }
  }
};

const void *DeadCodeEliminationPass::ID = reinterpret_cast<void *>(0x12345678);

} // namespace olc