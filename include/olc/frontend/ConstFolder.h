#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <variant>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

#include <olc/debug.h>

using namespace olc;

class ConstFoldVisitor : public sysy2022BaseVisitor {
  // 符号表
  SymTab<std::string, Value *> &symbolTable;

public:
  ConstFoldVisitor(SymTab<std::string, Value *> &symbolTable)
      : symbolTable(symbolTable) {}

  // 处理常量值,类似于:
  // const int b = 10;
  // int c = b;
  virtual std::any visitLVal(sysy2022Parser::LValContext *ctx) override {
    // 获取变量名
    std::string varName = ctx->ID()->getText();
    // 获取变量值, 若语义正确获得的应为常量全局变量.
    // FIXME: cast!
    // TODO: array!
    ConstantValue *result = cast<ConstantValue>(
        cast<GlobalVariable>(symbolTable.lookup(varName))->getInitializer());
    if (result) {
      if (result->isInt()) {
        result = new ConstantValue(result->getInt());
      } else if (result->isFloat()) {
        result = new ConstantValue(result->getFloat());
      } else {
        olc_unreachable("Invalid type for constant value");
      }
    } else {
      olc_unreachable("Variable not found");
    }
    return result;
  }

  virtual std::any
  visitAddSubExpr(sysy2022Parser::AddSubExprContext *ctx) override {
    ConstantValue *result = nullptr;

    // 获取左操作数
    auto leftAny = visit(ctx->expr(0));
    auto *left = std::any_cast<ConstantValue *>(leftAny);

    // 获取右操作数
    auto rightAny = visit(ctx->expr(1));
    auto *right = std::any_cast<ConstantValue *>(rightAny);

    // 进行常量折叠
    if (left && right) {
      if (ctx->op->getText() == "+") {
        if (left->isInt() && right->isInt()) {
          result = new ConstantValue(left->getInt() + right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          result = new ConstantValue(left->getFloat() + right->getFloat());
        } else {
          olc_unreachable("Invalid type for add operation");
        }
      } else if (ctx->op->getText() == "-") {
        if (left->isInt() && right->isInt()) {
          result = new ConstantValue(left->getInt() - right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          result = new ConstantValue(left->getFloat() - right->getFloat());
        } else {
          olc_unreachable("Invalid type for sub operation");
        }
      }
    } else {
      olc_unreachable("Invalid type for add/sub operation");
    }
    return result;
  }

  virtual std::any
  visitMulDivModExpr(sysy2022Parser::MulDivModExprContext *ctx) override {
    ConstantValue *result = nullptr;

    // 获取左操作数
    auto leftAny = visit(ctx->expr(0));
    auto *left = std::any_cast<ConstantValue *>(leftAny);

    // 获取右操作数
    auto rightAny = visit(ctx->expr(1));
    auto *right = std::any_cast<ConstantValue *>(rightAny);

    // 进行常量折叠
    if (left && right) {
      if (ctx->op->getText() == "*") {
        if (left->isInt() && right->isInt()) {
          result = new ConstantValue(left->getInt() * right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          result = new ConstantValue(left->getFloat() * right->getFloat());
        } else {
          olc_unreachable("Invalid type for mul operation");
        }
      } else if (ctx->op->getText() == "/") {
        if (left->isInt() && right->isInt()) {
          result = new ConstantValue(left->getInt() / right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          result = new ConstantValue(left->getFloat() / right->getFloat());
        } else {
          olc_unreachable("Invalid type for div operation");
        }
      } else if (ctx->op->getText() == "%") {
        if (left->isInt() && right->isInt()) {
          result = new ConstantValue(left->getInt() % right->getInt());
        } else {
          olc_unreachable("Invalid type for mod operation");
        }
      }
    } else {
      olc_unreachable("Invalid type for mul/div/mod operation");
    }
    return result;
  }

  virtual std::any
  visitSubUnaryExpr(sysy2022Parser::SubUnaryExprContext *ctx) override {
    return visit(ctx->unaryExpr());
  }

  virtual std::any
  visitParenExpr(sysy2022Parser::ParenExprContext *ctx) override {
    return visit(ctx->expr());
  }

  virtual std::any
  visitIntLiteral(sysy2022Parser::IntLiteralContext *ctx) override {
    std::string intStr = ctx->getText();
    int result = std::stoi(intStr, nullptr, 0);
    return new ConstantValue(result);
  }

  virtual std::any
  visitFloatLiteral(sysy2022Parser::FloatLiteralContext *ctx) override {
    std::string floatStr = ctx->getText();
    float result = std::stof(floatStr.c_str());
    return new ConstantValue(result);
  }

  virtual std::any
  visitRecUnaryExpr(sysy2022Parser::RecUnaryExprContext *ctx) override {
    ConstantValue *result = nullptr;
    ConstantValue *expr =
        std::any_cast<ConstantValue *>(visit(ctx->unaryExpr()));

    if (expr) {
      if (ctx->op->getText() == "+") {
        // do nothing
        result = expr;
      } else if (ctx->op->getText() == "-") {
        // -x
        if (expr->isInt()) {
          result = new ConstantValue(-expr->getInt());
        } else if (expr->isFloat()) {
          result = new ConstantValue(-expr->getFloat());
        }
      } else {
        olc_unreachable("Unsupported unary operator");
      }
    } else {
      olc_unreachable("Invalid expression for unary operation");
    }

    return result;
  }
};
