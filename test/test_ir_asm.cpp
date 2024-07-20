#include <iostream>

#include <olc/ir/IR.h>

int main() {
    // 创建一个 Function 对象
    Function mainFunction;
    mainFunction.name = "main";

    // 创建一个 BasicBlock 对象并添加到 Function 中
    BasicBlock *bb = new BasicBlock();
    mainFunction.basicBlocks.push_back(bb);

    // 创建一个 ReturnInstruction 对象
    ReturnInstruction *retInstr = new ReturnInstruction();

    // 创建一个 Constant 对象并作为 ReturnInstruction 的返回值
    Constant *constValue = new Constant(123);
    retInstr->ret.setValue(constValue);

    // 将 ReturnInstruction 添加到 BasicBlock 中
    bb->instructions.push_back(retInstr);

    // 打印 Function 的内容
    std::cout << "define i32 @" << mainFunction.name << "() {" << std::endl;
    std::cout << "    ret i32 " << constValue->value << std::endl;
    std::cout << "}" << std::endl;

    return 0;
}
