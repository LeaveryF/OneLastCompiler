
#pragma once

#include <iostream>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

class IRVisitor : public sysy2022BaseVisitor {
public:
  virtual std::any
  visitCompUnit(sysy2022Parser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(sysy2022Parser::DeclContext *ctx) override {
    return visitChildren(ctx);
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
    return visitChildren(ctx);
  }

  virtual std::any
  visitFuncFParams(sysy2022Parser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(sysy2022Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBlockItem(sysy2022Parser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(sysy2022Parser::StmtContext *ctx) override {
    int result = std::any_cast<int>(visit(ctx->expr()));
    std::cout << "return value: " << result << std::endl;
    return result;
  }

  virtual std::any visitExpr(sysy2022Parser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(sysy2022Parser::AddExprContext *ctx) override {
    int left = std::any_cast<int>(visit(ctx->mulExpr(0)));
    int right = std::any_cast<int>(visit(ctx->mulExpr(1)));
    return left + right;
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
    return std::stoi(ctx->INT()->getText());
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
