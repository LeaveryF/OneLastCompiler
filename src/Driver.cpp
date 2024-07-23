// ref:
// https://github.com/antlr/antlr4/blob/master/runtime/Cpp/demo/Windows/antlr4-cpp-demo/main.cpp

// ref: https://tomassetti.me/getting-started-antlr-cpp/
// https://github.com/gabriele-tomassetti/antlr-cpp/blob/master/antlr.cpp

#include <fstream>
#include <iostream>

#include <antlr4-runtime.h>
#include <sysy2022Lexer.h>
#include <sysy2022Parser.h>
#include <sysy2022Visitor.h>

#include <olc/frontend/Visitor.h>
#include <olc/ir/AsmWriter.h>
#include <olc/ir/IR.h>

using namespace antlr4;
using namespace olc;

Module *module = new Module{};

int main(int argc, const char *argv[]) {
  std::ifstream fin("../test/data/09_func_defn.sy");
  if (!fin) {
    std::cout << "File not found" << std::endl;
    return 1;
  }
  ANTLRInputStream input(fin);
  // ANTLRInputStream input("int main() { \n\treturn 0; \n}");

  sysy2022Lexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  sysy2022Parser parser(&tokens);
  // tree::ParseTree *parse_tree = parser.compUnit();

  // auto s = parse_tree->toStringTree(&parser);
  // std::cout << "Parse Tree: " << s << std::endl;

  sysy2022Parser::CompUnitContext *tree = parser.compUnit();

  AssemblyWriter asmWriter{std::cout};

  CodeGenASTVisitor visitor;
  visitor.visitCompUnit(tree);

  asmWriter.printModule(module);

  return 0;
}
