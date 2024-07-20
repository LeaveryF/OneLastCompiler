#include <iostream>

#include <olc/ir/AsmWriter.h>
#include <olc/ir/IR.h>

int main() {
  using namespace olc;

  AssemblyWriter asmWriter{std::cout};
  auto *mod = new Module{};
  Function *mainFunc = new Function{"main"};
  mod->addFunction(mainFunc);

  BasicBlock *entryBB = mainFunc->getEntryBlock();

  auto *op1 = new ConstantValue{24};
  auto *op2 = new ConstantValue{99};
  auto *sum = entryBB->create<BinaryInst>(Value::Tag::Add, op1, op2);
  auto *isEqual123 =
      entryBB->create<BinaryInst>(Value::Tag::Eq, sum, new ConstantValue(123));

  auto *retInst = entryBB->create<ReturnInst>(isEqual123);

  asmWriter.printModule(mod);

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

  asmWriter.printModule(mod);

  // 测试 classof
  assert(isa<BinaryInst>(isEqual123));
  assert(isa<BinaryInst>((Value *)isEqual123));
  assert(!isa<BinaryInst>((Value *)retInst));
  assert(!isa<Instruction>((Value *)op1));
  assert(isa<Instruction>((Value *)isEqual123));
  assert(isa<Instruction>((Value *)retInst));
  assert(isa<Instruction>((Value *)sum));
  assert(isa<User>((Value *)retInst));
  assert(!isa<User>((Value *)op1));

  // 新建函数
  Function *newFunc = new Function{"newFunc"};
  BasicBlock *newBlock = newFunc->getEntryBlock();
  auto *val = new ConstantArray{1.3f, 99};
  auto *instr = newBlock->create<BinaryInst>(Value::Tag::Div, val, val);
  std::cout << "==========================\n\n";
  mod->addFunction(newFunc);
  asmWriter.printModule(mod);
  // 测试重边 setOperand
  instr->setOperand(1, op1);
  asmWriter.printModule(mod);

  return 0;
}
