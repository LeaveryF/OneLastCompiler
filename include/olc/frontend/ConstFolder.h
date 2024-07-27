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
public:
  virtual std::any
  visitAddSubExpr(sysy2022Parser::AddSubExprContext *ctx) override {
    ConstantValue* result = nullptr;

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
    ConstantValue* result = nullptr;

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
    float result = 0.0;
    if (floatStr.substr(0, 2) == "0x" || floatStr.substr(0, 2) == "0X") {
      std::string hexStr = "0x0", fracStr = "0x0", expStr = "";
      int i = 2;
      while (floatStr[i] != '.' && floatStr[i] != 'p' && floatStr[i] != 'P') {
        hexStr += floatStr[i++];
      }
      if (floatStr[i] == '.') {
        i++;
      }
      result += std::stoi(hexStr.c_str(), nullptr, 16);
      while (floatStr[i] != 'p' && floatStr[i] != 'P') {
        fracStr += floatStr[i++];
      }
      i++;
      result +=
          std::stoi(fracStr.c_str(), nullptr, 16) / pow(16, fracStr.size() - 3);
      while (i < floatStr.size()) {
        expStr += floatStr[i++];
      }
      result *= pow(2, std::stoi(expStr.c_str(), nullptr, 10));
    } else {
      result = std::stof(floatStr.c_str(), nullptr);
    }
    return new ConstantValue(result);
  }

  virtual std::any
  visitRecUnaryExpr(sysy2022Parser::RecUnaryExprContext *ctx) override {
    ConstantValue* result = nullptr;
    ConstantValue* expr = std::any_cast<ConstantValue *>(visit(ctx->unaryExpr()));

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
