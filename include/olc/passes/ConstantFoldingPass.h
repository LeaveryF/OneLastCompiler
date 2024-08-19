#include <olc/ir/IR.h>
#include <olc/passes/Pass.h>
#include <unordered_map>

namespace olc {

ConstantValue *
ConstFold(BinaryInst *binInst, ConstantValue *lhs, ConstantValue *rhs);
class ConstantFoldingPass : public FunctionPass {
public:
  ConstantFoldingPass() : FunctionPass(&ID) {}

  bool runOnFunction(Function &function) override {
    bool modified = false;
    std::unordered_map<Value *, ConstantValue *> memoryMap;

    // 遍历函数中的每一个基本块
    for (auto &block : function.getBasicBlocks()) {
      // 遍历基本块中的每一条指令
      for (auto it = block->instructions.begin();
           it != block->instructions.end();) {
        Instruction *inst = *it++;

        // 检查是否是二元运算指令
        if (auto binInst = dyn_cast<BinaryInst>(inst)) {
          // 获取操作数
          if (auto lhs = dyn_cast<ConstantValue>(binInst->getLHS())) {
            if (auto rhs = dyn_cast<ConstantValue>(binInst->getRHS())) {
              // 计算结果
              ConstantValue *result = ConstFold(binInst, lhs, rhs);
              // 替换指令
              if (result) {
                inst->replaceAllUseWith(result);
                block->instructions.erase(std::prev(it));
                modified = true;
              }
            }
          }
        }
      }
    }

    return modified;
  }

  std::string getName() const override { return "ConstantFoldingPass"; }

private:
  static const void *ID;
};

const void *ConstantFoldingPass::ID = reinterpret_cast<void *>(0xCF240816);

} // namespace olc