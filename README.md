# OneLastCompiler

- 2024.12.24 已由赛事方gitlab迁移至github

## 项目介绍

- 项目介绍:
  
  项目名称为OneLastCompiler 一个SysY2022语言的编译器  
  为 2024年全国大学生计算机系统能力大赛-编译系统设计赛-编译系统实现赛 设计  
  其功能是将SysY2022语言(一种简化的C语言子集)的源代码(.sy文件)编译为ARMv7指令集的目标代码(.s文件)  
  项目使用语言为C++17 基于CMake构建  

- 代码行数:
  
  开发版本 8469 line  
  提交版本 8472 line  

- 项目最终成绩:
  
  2024年全国大学生计算机系统能力大赛-编译系统设计赛-编译系统实现赛-决赛  
  ARM赛道5/12 三等奖  
  功能100(20%) 性能50.48(70%) 专家打分82.20(10%)  
  总分63.56

- 大赛地址:

  大赛首页: https://compiler.educg.net/#/index?TYPE=COM  
  比赛章程: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/2024全国大学生计算机系统能力培养大赛编译系统设计赛-章程.pdf  
  技术方案: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/2024全国大学生计算机系统能力大赛-编译系统设计编译系统实现赛道技术方案V1.1.pdf  
  
  获奖名单: https://mp.weixin.qq.com/s/QAGkyzMGqV6lS4EkyQFBXg  
  最终成绩: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/2024年编译系统设计赛最终成绩.pdf  

- 项目地址:
  
  现已迁移至github: https://github.com/LeaveryF/OneLastCompiler  
  开发版本gitlab: https://gitlab.eduxiji.net/T202410013203408/compiler  
  提交版本gitlab: https://gitlab.eduxiji.net/T202410013203408/onelastcompiler  
  (提交版本不含test目录 多了预处理脚本run.py 预处理了头文件 可以使用gcc直接编译)  
  赛后仓库公开: https://gitlab.eduxiji.net/educg-group-26172-2487152/T202410013203408-4017  
  (是最后一次提交仓库的副本)  

## 项目特色

- 使用CMake构建 跨平台  
- 架构上分为前中后三端  
- 前端使用ANTLR生成词法和语法解析器 简易便捷  
- 使用ANTLR提供的访问器visitor 通过访问者模式直接遍历语法分析树ParseTree生成IR  
  (见include/olc/frontend/Visitor.h)  
- 可以识别语法错误和部分语义错误 并给出相应的报错信息  
- 中端使用类LLVM的SSA形式的IR  
  (见include/olc/ir/IR.h)  
- 使用硬件浮点指令VFP 提高效率  
- 可以链接外部库libsysy.a  
- 具有多个优化Pass 具体优化pass介绍见下文  
  (见include/olc/passes/*.h)  
- 项目初期使用基于汇编字符串拼接、纯栈分配的简易后端 保证了功能的正确性  
  (见include/olc/backend/ArmWriter.h)  
- 项目后期重新构建后端低层次LIR(Machine IR) 便于进行寄存器分配、指令选择、窥孔优化等工作  
  (见include/olc/backend/MachineIR.h)  
- 具有多种中间形式用于调试的输出  
  (见include/olc/ir/AsmWriter.h 用于输出IR)  
  (见include/olc/backend/CodeWriter.h 用于输出Machine IR)  

## 项目文件

- antlr/: ANTLR生成的文件 包括lexer/parser/visitor 生成一次后直接使用即可 具体介绍见antlr/README  

- cmake/: ANTLR相关的cmake构建文件 来自https://github.com/antlr/antlr4/tree/master/runtime/Cpp/cmake  

- include/: 头文件  

- 后端其它重要文件介绍:  
  include/olc/backend/CodeGen.h: 由中端IR 生成后端Machine IR 即指令选择 包含了乘除优化  
  include/olc/backend/ArmGen.h: 由后端Machine IR 生成ARM汇编代码 包含了寄存器分配和窥孔优化  
  include/olc/backend/Liveness.h: 寄存器分配需要用到的活跃变量分析  
  include/olc/backend/RegAlloc.h: 线性扫描寄存器分配  

- 优化pass介绍:  
  - include/olc/passes/Pass.h: pass基类  
    include/olc/passes/Passes.h: 所有pass的头文件  
    include/olc/passes/PassManager.h: 管理所有pass  

  - include/olc/passes/SimplifyCFGPass.h: 简化控制流图  
    include/olc/passes/DCEProPass.h: 死代码删除  

  - include/olc/passes/DominanceAnalysis.h: 作用域分析 辅助Mem2Reg的使用  
    include/olc/passes/Mem2Reg.h: SSA转换算法 转化为SSA形式的IR phi生成和phi消去  

  - include/olc/passes/ConstantFoldingPass.h: 常量折叠 并没有单独使用 包含在了SCCP中  
    include/olc/passes/SCCPPass.h: 稀疏条件常量传播  
    该pass暂无效果 开启后部分样例性能变低 最终提交版本没有开启该pass 与之相关的CanonicalizePass.h和CodeGen.h中的四个assert需要被注释  

  - include/olc/passes/CanonicalizePass.h: 代数化简/规范化 辅助GVNGCN的使用  
    include/olc/passes/GVNGCMPass.h: 全局值编号和全局代码移动 自动包含了传统的循环不变量外提LICM  

  - 各个优化pass需要注意使用顺序 可能需要重复交叠使用 见Driver.cpp  

- src/: 源文件  
  大部分代码实际上都在.h文件中书写了 不含对应的.cpp文件  
  src/Driver.cpp: 主函数(提交版本为main.cpp)  

- test/: 测试文件 包括测试源文件和测试数据文件(放在data/下) 但不含.in和.out文件 (提交版本不含该目录)  

- build/: CMake构建生成文件 仅当使用CMake构建时生成  
  测试脚本应放在该目录下 项目中并不含测试脚本  
  外部库libsysy.a也应放在该目录下  
  第一次构建也会从ANTLR官方github克隆antlr4-runtime源码到该目录下 可能会需要一段时间  
  
- 提交仓库的run.py: 使用rsync同步放在同一目录下的开发仓库和提交仓库 预处理头文件便于使用gcc直接编译  

## 项目运行

- 项目运行:
  
  git clone到本地  
  加载CMakeList.txt  
  构建整个项目并运行  
  将在build/下生成main.exe可执行文件(提交版本为compiler.exe)  
  程序输入为SysY2022语言源文件(.sy文件) 输出为ARMv7指令集目标文件(.s文件)  

  开发版本和提交版本命令行参数形式都形如compiler testcase.sysy -S -o testcase.s -O1  
  如果不指定输入文件 程序会默认以test/data/test.sy为输入 需要注意提交版本并不存在test目录  
  所有中间输出全部输出到stderr 只有最终需要的汇编代码输出到标准输出stdout 需要输出到文件时可以使用-o参数或在命令行使用重定向  
  开发版本总是以-O1模式运行 即总是开启所有pass 而提交版本在没有-O1参数时 会使用旧的简易后端 因为新后端实际上存在部分功能样例不过的情况  
  提交版本也可以使用gcc直接编译 编译命令参考https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/compile.java  

- 硬件环境模拟:
  
  安装arm-linux-gnueabihf-gcc交叉编译器:  
  sudo apt-get install gcc-arm-linux-gnueabihf  
  安装QEMU模拟器:  
  sudo apt-get install qemu-user-static  

# 参考

- 参考外部代码:
  
  LLVM project: https://github.com/llvm/llvm-project/  
  清华 - 2020 - TrivialCompiler: https://github.com/TrivialCompiler/TrivialCompiler  
  北航 - 2023 - MeowCompiler(参考了其乘除优化): https://gitlab.eduxiji.net/educg-group-18973-1895971/compiler2023-202310006201934  
  中科大 - SysYF-CodeGenOpt(参考了其SCCP): https://github.com/liuly0322/sysyf_compiler_codegen_opt  

- 参考文献:
  
  [1] Muchnick, Steven. Advanced Compiler Design and Implementation. Morgan Kaufmann, 1997.  
  《高级编译器设计与实现》  
  [2] Torczon, Linda, and Keith Cooper. Engineering a Compiler. Morgan Kaufmann Publishers Inc., 2007.  
  《编译器设计 - 第二版》  
  [3] Granlund, Torbjörn, and Peter L. Montgomery. “Division by Invariant Integers Using Multiplication.” Proceedings of the ACM SIGPLAN 1994 Conference on Programming Language Design and Implementation, 1994, pp. 61–72.  
  《Division by Invariant Integers Using Multiplication》  
  [4] Various Authors. Static Single Assignment Book, 2018  
  《Static Single Assignment Book》  

- 其它参考资料:
  
  (更多antlr相关资料 见antlr/README)
  antlr官网: https://www.antlr.org  
  antlr github: https://github.com/antlr/antlr4  
  antlr c++ runtime文档: https://github.com/antlr/antlr4/tree/master/runtime/Cpp  
  antlr语法示例: https://github.com/antlr/grammars-v4  
  
  SysY 语言定义: https://gitlab.eduxiji.net/csc1/nscscc/compiler2023/-/blob/master/SysY2022语言定义-V1.pdf  
  SysY 运行时库: https://gitlab.eduxiji.net/csc1/nscscc/compiler2023/-/blob/master/SysY2022运行时库-V1.pdf  
  C99文档 - ISO/IEC 9899 - n1124: https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf  
  
  LLVM documentation: https://llvm.org/docs  
  LLVM tutorial: https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/index.html  
  中文部分: https://kaleidoscope-llvm-tutorial-zh-cn.readthedocs.io/zh-cn/latest/  
  中文机翻: https://www.bookstack.cn/read/llvm-guide-zh  
  LLVM RTTI: https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html  
  LLVM IR lang ref: https://llvm.org/docs/LangRef.html  
  LLVM Programmer Manual: https://llvm.org/docs/ProgrammersManual.html  
  Getting Started with LLVM Core Libraries: https://getting-started-with-llvm-core-libraries-zh-cn.readthedocs.io/zh-cn/latest/  
  Mapping High Level Constructs to LLVM IR: https://mapping-high-level-constructs-to-llvm-ir.readthedocs.io/en/latest/basic-constructs/  
  
  LLVM介绍: https://linux.cn/article-6073-1.html  
  IR介绍: https://www.cnblogs.com/whiteBear/p/16717687.html  
  SSA IR: https://blog.csdn.net/raojun/article/details/103629894  
  Value、User、Use: https://zhuanlan.zhihu.com/p/689591662  
  A Tour to LLVM IR (上): https://zhuanlan.zhihu.com/p/66793637  
  A Tour to LLVM IR (下): https://zhuanlan.zhihu.com/p/66909226  
  
  Compiler Explorer: https://godbolt.org/  
  
  ARM和Thumb-2指令集快速参考卡: https://gitlab.eduxiji.net/csc1/nscscc/compiler2021/-/blob/master/ARM和Thumb-2指令集快速参考卡.pdf  
  ARM ABI: https://github.com/ARM-software/abi-aa/releases  
  ARM ABI Base Standard: https://github.com/ARM-software/abi-aa/blob/2a70c42d62e9c3eb5887fa50b71257f20daca6f9/bsabi32/bsabi32.rst  
  ARM Procedure Call Standard: https://github.com/ARM-software/abi-aa/blob/2a70c42d62e9c3eb5887fa50b71257f20daca6f9/aapcs32/aapcs32.rst  
  ARM Run-time ABI: https://github.com/ARM-software/abi-aa/blob/2a70c42d62e9c3eb5887fa50b71257f20daca6f9/rtabi32/rtabi32.rst  
  ARM开发者官网: https://developer.arm.com/  
  ARMv7文档: https://developer.arm.com/documentation/den0013/latest/  
  ARM32 ABI 约定 - Microsoft文档: https://learn.microsoft.com/zh-cn/cpp/build/overview-of-arm-abi-conventions  
  
  ARM汇编: https://blog.csdn.net/Luckiers/article/details/128221506  
  ARM汇编: https://www.cnblogs.com/quan0311/p/15025108.html  
  ARM指令集: https://blog.csdn.net/mickey35/article/details/82011449  
  GNU汇编语法: https://blog.csdn.net/daocaokafei/article/details/115439936  
  VFP: https://www.cnblogs.com/wheater/p/16538217.html  
  
  ARM常量池: https://www.jianshu.com/p/4c8194045201  
  ARM directives: https://developer.arm.com/documentation/den0013/d/Introduction-to-Assembly-Language/Introduction-to-the-GNU-Assembler/Assembler-directives  
  ARM ltorg: https://developer.arm.com/documentation/dui0489/i/directives-reference/ltorg  
  
  Division by Invariant Integers using Multiplication: https://gmplib.org/~tege/divcnst-pldi94.pdf  
  CSDN相关文章: https://blog.csdn.net/yiran103/article/details/136837557  
  知乎文章: https://zhuanlan.zhihu.com/p/151038723  
  相关博客: https://thysrael.github.io/posts/4848be12/  
  
  SCCP: https://blog.csdn.net/qq_36287943/article/details/104974597  
  SCCP: https://blog.liuly.moe/posts/compiler  
  中科大 - SysYF-CodeGenOpt - SCCP: https://github.com/liuly0322/sysyf_compiler_codegen_opt/blob/main/SysYF_Pass_Student/src/Optimize/SCCP.cpp  
  
  北航 miniSysY 编译实验: https://buaa-se-compiling.github.io/miniSysY-tutorial/  
  清华 MiniDecaf 编译实验: https://decaf-lang.github.io/minidecaf-tutorial/  
  北大 SysY 编译实验: https://pku-minic.github.io/online-doc/  
  
- 大赛地址:
  
  系统能力大赛首页: https://compiler.educg.net  
  大赛首页: https://compiler.educg.net/#/index?TYPE=COM  
  大赛平台: https://course.educg.net/sv2/indexexp/contest/contest.jsp?contestID=Y056z7F6v3o  
  
  大赛gitlab: https://gitlab.eduxiji.net  
  比赛章程、技术方案、测试数据、运行时库、决赛数据: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024  
  技术培训: https://live.eyunbo.cn/live/138795?uin=1729  
  
  赛后通道: https://compiler.educg.net/#/index?TYPE=MN_COM  
  赛后通道: https://course.educg.net/sv2/indexexp/contest/contest.jsp?contestID=pRAjDdbXXFM  
  
- 赛事通知/赛事其它相关链接:
  (来自微信公众号-计算机系统能力培养)
  
  2023决赛获奖名单: https://mp.weixin.qq.com/s/Tq5qTIYBBbDHwEtfaVnVXg  
  2023决赛总结: https://mp.weixin.qq.com/s/4LE2KHwPYkXQeLhSWYJ-Vw  
  
  初赛提醒: https://mp.weixin.qq.com/s/W3MU08V329RW_e3kVLtBJA  
  入围名单: https://mp.weixin.qq.com/s/3BJQmqNSfxiMLsuhstPKrw  
  
  答辩通知: https://mp.weixin.qq.com/s/uonggUyLRui8JlYgiKY2Fw  
  颁奖通知: https://mp.weixin.qq.com/s/IMmBCTBEnupmcRo1jLYK0A  
  重要事项: https://mp.weixin.qq.com/s/TWQrTU45KzoKibeEjCMMmQ  
  竞赛手册: https://mp.weixin.qq.com/s/pXcSfTFcviz-hTvF-RZJyg  
  (对应都有pdf文件见 https://gitlab.eduxiji.net/csc1/nscscc/compiler2024)  
  
  颁奖预告: https://mp.weixin.qq.com/s/U400MYjS1dhpOXGtieHd4A  
  图片直播: https://m.alltuu.com/album/1545741704/?menu=live  
  直播回放: https://live.eyunbo.cn/live/144438?uin=1729  
  获奖名单: https://mp.weixin.qq.com/s/QHPpxp412bocEhfy4_zF6A  
  
  各队仓库: https://gitlab.eduxiji.net/educg-group-26172-2487152  
  SysY代码生成器: https://github.com/dusk-phantom/sysmith  
  知乎评价: https://www.zhihu.com/question/664985544  
  
  获奖名单: https://mp.weixin.qq.com/s/QAGkyzMGqV6lS4EkyQFBXg  
  复核说明: https://mp.weixin.qq.com/s/MBdLa2erNtnFj77waBNdSQ  
  最终成绩: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/2024年编译系统设计赛最终成绩.pdf  
  成绩明细: https://gitlab.eduxiji.net/csc1/nscscc/compiler2024/-/blob/main/2024年编译系统设计赛ARM赛道重测明细.pdf  
  (其它复核相关说明见 https://gitlab.eduxiji.net/csc1/nscscc/compiler2024)  
