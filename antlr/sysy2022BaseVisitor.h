
// Generated from sysy2022.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "sysy2022Visitor.h"


/**
 * This class provides an empty implementation of sysy2022Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  sysy2022BaseVisitor : public sysy2022Visitor {
public:

  virtual std::any visitCompUnit(sysy2022Parser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(sysy2022Parser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(sysy2022Parser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDecl(sysy2022Parser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(sysy2022Parser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstInitVal(sysy2022Parser::ConstInitValContext *ctx) override {
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

  virtual std::any visitFuncType(sysy2022Parser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(sysy2022Parser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(sysy2022Parser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(sysy2022Parser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStmt(sysy2022Parser::AssignStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprStmt(sysy2022Parser::ExprStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStmt(sysy2022Parser::BlockStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(sysy2022Parser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStmt(sysy2022Parser::WhileStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(sysy2022Parser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(sysy2022Parser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(sysy2022Parser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(sysy2022Parser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpr(sysy2022Parser::AddExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExpr(sysy2022Parser::MulExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpr(sysy2022Parser::UnaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOp(sysy2022Parser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(sysy2022Parser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(sysy2022Parser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(sysy2022Parser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(sysy2022Parser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCond(sysy2022Parser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExpr(sysy2022Parser::LOrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndExpr(sysy2022Parser::LAndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(sysy2022Parser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExpr(sysy2022Parser::RelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExpr(sysy2022Parser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }


};

