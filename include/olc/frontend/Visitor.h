
#pragma once

#include <iostream>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

using namespace olc;

extern Module *module;
utils::SymTab<std::string, std::string> *symtab =
    new utils::SymTab<std::string, std::string>;

// TODO: replace this class with your visitor
class DebugASTVisitor : public sysy2022BaseVisitor {
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
    // 函数名加到符号表中
    symtab->insert(
        ctx->ID()->getText(),
        std::any_cast<std::string>(visit(ctx->funcType())));
    // 进入新的作用域
    symtab->enterScope();

    // 初始化函数
    Function *function = new Function(ctx->ID()->getText());
    // 处理形参
    if (ctx->funcFParams() != nullptr) {
      std::vector<std::pair<std::string, std::string>> params =
          std::any_cast<std::vector<std::pair<std::string, std::string>>>(
              visit(ctx->funcFParams()));
      for (const auto &param : params) {
        // 加到Function类中
        function->args.push_back(new Argument(param.first));
        // 加到符号表中
        symtab->insert(param.first, param.second);
      }
    }
    // 加到module中
    module->addFunction(function);

    // 处理函数体
    visit(ctx->block());
    // 退出作用域
    symtab->exitScope();

    return 0;
  }

  virtual std::any
  visitFuncType(sysy2022Parser::FuncTypeContext *ctx) override {
    return ctx->getText();
  }

  virtual std::any
  visitFuncFParams(sysy2022Parser::FuncFParamsContext *ctx) override {
    std::vector<std::pair<std::string, std::string>> params;
    for (int i = 0; i < ctx->funcFParam().size(); i++) {
      params.push_back(std::any_cast<std::pair<std::string, std::string>>(
          visit(ctx->funcFParam(i))));
    }
    return params;
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    return std::make_pair(ctx->ID()->getText(), ctx->basicType()->getText());
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
