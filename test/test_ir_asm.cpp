#include <iostream>

#include <olc/ir/IR.h>

int main() {
  using namespace olc;

  // 创建一个 Function 对象
  Function *mainFunc = new Function{"main"};

  BasicBlock *entryBB = mainFunc->getEntryBlock();

  auto *retInst = entryBB->create<ReturnInst>(new ConstantValue(123));

  // mainFunc->print();

  return 0;
}
