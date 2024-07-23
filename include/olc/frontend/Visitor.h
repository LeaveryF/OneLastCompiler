
#pragma once

#include <iostream>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

using namespace olc;

class CodeGenASTVisitor : public sysy2022BaseVisitor {
  utils::SymTab<std::string, Value *> valueMap;
  utils::SymTab<std::string, Type *> typeMap;
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
  virtual std::any
  visitCompUnit(sysy2022Parser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(sysy2022Parser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBasicType(sysy2022Parser::BasicTypeContext *ctx) override {
    return ctx->getText();
  }

  virtual std::any
  visitConstDecl(sysy2022Parser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitConstDef(sysy2022Parser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitConstInitVal(sysy2022Parser::ConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(sysy2022Parser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(sysy2022Parser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitVal(sysy2022Parser::InitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(sysy2022Parser::FuncDefContext *ctx) override {
    // 进入新的作用域
    typeMap.enterScope();
    valueMap.enterScope();

    // 初始化函数
    auto *retType = convertType(ctx->funcType()->getText());
    std::vector<Type *> argTypes;
    std::vector<Argument *> args;

    // 处理形参
    if (ctx->funcFParams() != nullptr) {
      auto params =
          std::any_cast<std::vector<Argument *>>(visit(ctx->funcFParams()));
      for (const auto &param : ctx->funcFParams()->funcFParam()) {
        auto *type = convertType(param->basicType()->getText());
        argTypes.push_back(type);
        args.push_back(new Argument{type, param->ID()->getText()});
      }
    }
    // 加到module中
    // 函数名加到符号表中
    auto *funcType = FunctionType::get(retType, argTypes);
    Function *function = new Function(funcType, ctx->ID()->getText(), args);
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
  visitFuncType(sysy2022Parser::FuncTypeContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  virtual std::any
  visitFuncFParams(sysy2022Parser::FuncFParamsContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  virtual std::any visitBlock(sysy2022Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBlockItem(sysy2022Parser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitAssignStmt(sysy2022Parser::AssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitExprStmt(sysy2022Parser::ExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBlockStmt(sysy2022Parser::BlockStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(sysy2022Parser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitWhileStmt(sysy2022Parser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBreakStmt(sysy2022Parser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitContinueStmt(sysy2022Parser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitReturnStmt(sysy2022Parser::ReturnStmtContext *ctx) override {
    // int result = std::any_cast<int>(visit(ctx->expr()));
    // std::cout << "return value: " << result << std::endl;
    // return result;
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(sysy2022Parser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(sysy2022Parser::AddExprContext *ctx) override {
    // int left = std::any_cast<int>(visit(ctx->mulExpr(0)));
    // int right = std::any_cast<int>(visit(ctx->mulExpr(1)));
    // return left + right;
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(sysy2022Parser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitUnaryExpr(sysy2022Parser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOp(sysy2022Parser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitFuncRParams(sysy2022Parser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitPrimaryExpr(sysy2022Parser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(sysy2022Parser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(sysy2022Parser::NumberContext *ctx) override {
    // return std::stoi(ctx->INT()->getText());
    return visitChildren(ctx);
  }

  virtual std::any visitCond(sysy2022Parser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExpr(sysy2022Parser::LOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitLAndExpr(sysy2022Parser::LAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(sysy2022Parser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExpr(sysy2022Parser::RelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitConstExpr(sysy2022Parser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }
};
