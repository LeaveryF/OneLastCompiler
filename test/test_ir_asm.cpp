#include <iostream>

#include <olc/ir/IR.h>

int main() {
  using namespace olc;

  // 创建一个 Function 对象
  Function *mainFunc = new Function{"main"};

  BasicBlock *entryBB = mainFunc->getEntryBlock();

  auto *op1 = new ConstantValue{24};
  auto *op2 = new ConstantValue{99};
  auto *sum = entryBB->create<BinaryInst>(Value::Add, op1, op2);
  auto *isEqual123 =
      entryBB->create<BinaryInst>(Value::Eq, sum, new ConstantValue(123));

  auto *retInst = entryBB->create<ReturnInst>(isEqual123);

  // 打印指针：
  std::cout << "op1: " << op1 << std::endl;
  std::cout << "op2: " << op2 << std::endl;
  std::cout << "sum: " << sum << std::endl;
  std::cout << "isEqual123: " << isEqual123 << std::endl;
  std::cout << "retInst: " << retInst << std::endl;

#define PRINT_USE_LIST(var)                                                    \
  std::cout << "Use list of " #var ":" << std::endl;                           \
  for (auto &use : var->uses) {                                                \
    std::cout << "  User: " << use.user << ", index: " << use.index            \
              << std::endl;                                                    \
  }                                                                            \
  std::cout << "====" << std::endl;

  auto printInfo = [&] {
    PRINT_USE_LIST(op1);
    PRINT_USE_LIST(op2);
    PRINT_USE_LIST(sum);
    PRINT_USE_LIST(isEqual123);
    PRINT_USE_LIST(retInst);
  };

  printInfo();

  // 直接导向 sum
  retInst->setOperand(0, sum);
  printInfo();

  // 全部替换为 op1
  sum->replaceAllUseWith(op1);
  printInfo();

  // mainFunc->print();

  return 0;
}
