
#pragma once

#include <iostream>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

using namespace olc;

class CodeGenASTVisitor : public sysy2022BaseVisitor {
  SymTab<std::string, Value *> valueMap;
  SymTab<std::string, Type *> typeMap;
  Module *curModule;

  Type *convertType(std::string const &typeStr) {
    if (typeStr == "int") {
      return IntegerType::get();
    } else if (typeStr == "float") {
      return FloatType::get();
    } else if (typeStr == "void") {
      return VoidType::get();
    }
    olc_unreachable("NYI");
    return nullptr;
  }

public:
  CodeGenASTVisitor(Module *module) : curModule(module) {}

  virtual std::any
  visitCompUnit(sysy2022Parser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(sysy2022Parser::FuncDefContext *ctx) override {
    // 进入新的作用域
    typeMap.enterScope();
    valueMap.enterScope();

    // 初始化函数
    auto *retType = convertType(ctx->funcType->getText());
    std::vector<Argument *> args;

    // 处理形参
    if (ctx->funcFParam().size() > 0) {
      for (const auto &param : ctx->funcFParam()) {
        auto *type = convertType(param->basicType->getText());
        args.push_back(new Argument{type, param->ID()->getText()});
      }
    }
    // 加到module中
    // 函数名加到符号表中
    Function *function = new Function(retType, ctx->ID()->getText(), args);
    valueMap.insert(ctx->ID()->getText(), function);
    curModule->addFunction(function);

    // 处理函数体
    visit(ctx->block());

    // 退出作用域
    valueMap.exitScope();
    typeMap.exitScope();

    return {};
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }
};
