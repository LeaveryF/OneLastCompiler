
#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

using namespace olc;

class ConstFoldVisitor : public sysy2022BaseVisitor {
  // 符号表
  SymTab<std::string, Value *> symbolTable;
//   // 结点返回值
//   std::map<antlr4::ParserRuleContext *, Value *> valueMap;
//   // 当前模块
//   Module *curModule;
//   // 当前函数
//   Function *curFunction;
//   // 当前基本块
//   BasicBlock *curBasicBlock;

public:
  virtual std::any
  visitAddSubExpr(sysy2022Parser::AddSubExprContext *ctx) override {
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
          return new ConstantValue(left->getInt() + right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          return new ConstantValue(left->getFloat() + right->getFloat());
        }
      } else if (ctx->op->getText() == "-") {
        if (left->isInt() && right->isInt()) {
          return new ConstantValue(left->getInt() - right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          return new ConstantValue(left->getFloat() - right->getFloat());
        }
      }
    }
    return {};
  }

  virtual std::any
  visitMulDivModExpr(sysy2022Parser::MulDivModExprContext *ctx) override {
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
          return new ConstantValue(left->getInt() * right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          return new ConstantValue(left->getFloat() * right->getFloat());
        }
      } else if (ctx->op->getText() == "/") {
        if (left->isInt() && right->isInt()) {
          return new ConstantValue(left->getInt() / right->getInt());
        } else if (left->isFloat() && right->isFloat()) {
          return new ConstantValue(left->getFloat() / right->getFloat());
        }
      } else if (ctx->op->getText() == "%") {
        if (left->isInt() && right->isInt()) {
          return new ConstantValue(left->getInt() % right->getInt());
        }
      }
    }
    return {};
  }

  virtual std::any
  visitSubUnaryExpr(sysy2022Parser::SubUnaryExprContext *ctx) override {
    auto unaryAny = visit(ctx->unaryExpr());
    auto *unary = std::any_cast<ConstantValue *>(unaryAny);
    if (unary) {
      if (unary->isInt()) {
        return new ConstantValue(-unary->getInt());
      } else if (unary->isFloat()) {
        return new ConstantValue(-unary->getFloat());
      }
    }
    return {};
  }

  virtual std::any
  visitIntLiteral(sysy2022Parser::IntLiteralContext *ctx) override {
    std::string intStr = ctx->getText();
    int base = 10;
    if (intStr.substr(0, 2) == "0x" || intStr.substr(0, 2) == "0X") {
      base = 16;
    } else if (intStr.substr(0, 1) == "0") {
      base = 8;
    }
    int result = std::stoi(intStr, nullptr, base);
    return new ConstantValue(result);
  }

  virtual std::any
  visitFloatLiteral(sysy2022Parser::FloatLiteralContext *ctx) override {
    std::string floatStr = ctx->getText();
    float result = std::stof(floatStr);
    return new ConstantValue(result);
  }
};
