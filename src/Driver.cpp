// ref:
// https://github.com/antlr/antlr4/blob/master/runtime/Cpp/demo/Windows/antlr4-cpp-demo/main.cpp

// ref: https://tomassetti.me/getting-started-antlr-cpp/
// https://github.com/gabriele-tomassetti/antlr-cpp/blob/master/antlr.cpp

#include <fstream>
#include <iostream>
#include <sstream>

#include <antlr4-runtime.h>
#include <sysy2022Lexer.h>
#include <sysy2022Parser.h>
#include <sysy2022Visitor.h>

#include <olc/backend/ArmWriter.h>
#include <olc/backend/Liveness.h>
#include <olc/frontend/Visitor.h>
#include <olc/ir/AsmWriter.h>
#include <olc/ir/IR.h>

using namespace antlr4;
using namespace olc;

int main(int argc, const char *argv[]) {
  // 多文件批量测试
  // std::ifstream testin("../test/data.txt");
  // std::string fname;
  // std::ofstream logout("logs.txt");
  // std::ofstream errout("errs.txt");
  // std::streambuf *oldCerrBuf = std::cerr.rdbuf(errout.rdbuf());
  // while (std::getline(testin, fname)) {
  //   logout << fname << ':' << std::endl;
  //   errout << fname << ':' << std::endl;
  //   std::cout << fname << ':' << std::endl;
  //   std::ifstream fin("../test/" + fname);

  // 单文件测试
  std::ifstream fin("../test/data/test.sy");
  if (!fin) {
    std::cout << "File not found" << std::endl;
    return 1;
  }
  ANTLRInputStream input(fin);
  // ANTLRInputStream input("int main() { \n\treturn 0; \n}");

  sysy2022Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  // 输出解析树
  // sysy2022Parser parser(&tokens);
  // tree::ParseTree *parse_tree = parser.compUnit();
  // auto s = parse_tree->toStringTree(&parser);
  // std::cout << "Parse Tree: " << s << std::endl;

  // 输出中间代码
  sysy2022Parser parser(&tokens);
  sysy2022Parser::CompUnitContext *tree = parser.compUnit();

  AssemblyWriter asmWriter{std::cerr};

  // 输出到logs.txt
  // AssemblyWriter asmWriter{logout};

  auto *mod = new Module{};
  SymbolTable symbolTable;
  ConstFoldVisitor constFolder(symbolTable);
  CodeGenASTVisitor visitor(mod, constFolder, symbolTable);
  visitor.visitCompUnit(tree);

  asmWriter.printModule(mod);

  std::stringstream ss;
  ArmWriter armWriter{ss};
  armWriter.printModule(mod);

  std::cout << ss.str();
  std::cerr << ss.str();
  std::cerr << "============\n";

  // LivenessAnalysis liveness;
  // liveness.runOnFunction(mod->getFunction("main"));

  // auto getValName = [&](Value *val) {
  //   assert(val->isDefVar() && "Value is not a variable");
  //   if (auto *inst = dyn_cast<Instruction>(val)) {
  //     return asmWriter.nameManager[inst];
  //   } else {
  //     return cast<Argument>(val)->argName;
  //   }
  // };

  // for (auto &&[val, intv] : liveness.liveIntervals) {
  //   std::cout << "Var %" << getValName(val) << " live interval: [" << intv.first
  //             << ", " << intv.second << "]\n";
  // }

  return 0;
}
