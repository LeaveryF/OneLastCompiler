
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

class CodeGenASTVisitor : public sysy2022BaseVisitor {
  // 符号表
  SymTab<std::string, Value *> symbolTable;
  // 结点返回值
  std::map<antlr4::ParserRuleContext *, Value *> valueMap;
  // 当前模块
  Module *curModule;
  // 当前函数
  Function *curFunction;
  // 当前基本块
  BasicBlock *curBasicBlock;

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

  // 声明部分
  virtual std::any visitVarDecl(sysy2022Parser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(sysy2022Parser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitVal(sysy2022Parser::InitValContext *ctx) override {
    return visitChildren(ctx);
  }

  // 函数部分
  virtual std::any visitFuncDef(sysy2022Parser::FuncDefContext *ctx) override {
    // 初始化函数
    auto *retType = convertType(ctx->funcType->getText());
    std::vector<Argument *> args;

    // 处理形参
    for (const auto &param : ctx->funcFParam()) {
      auto *type = convertType(param->basicType->getText());
      args.push_back(new Argument{type, param->ID()->getText()});
    }
    // 加到module中
    Function *function = new Function(retType, ctx->ID()->getText(), args);
    curModule->addFunction(function);
    curFunction = function;
    curBasicBlock = *function->basicBlocks.begin();

    // 生成alloca指令

    // 函数名加到顶层符号表
    symbolTable.insert(ctx->ID()->getText(), function);

    // 进入新的作用域
    symbolTable.enterScope();
    // 参数加到符号表中
    for (const auto &arg : args) {
      symbolTable.insert(arg->argName, arg);
    }

    // 处理函数体
    visit(ctx->block());

    // 退出作用域
    symbolTable.exitScope();

    return {};
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  // 语句部分
  virtual std::any visitBlock(sysy2022Parser::BlockContext *ctx) override {
    // 进入新的作用域
    symbolTable.enterScope();

    // 处理块项目
    visitChildren(ctx);

    // 退出作用域
    symbolTable.exitScope();

    return {};
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
    if (ctx->expr() != nullptr) {
      // 获取子操作数
      visit(ctx->expr());
      auto *retVal = valueMap.at(ctx->expr());
      // 创建指令
      Value *result = curBasicBlock->create<ReturnInst>(retVal);
    } else {
    }
    return {};
  }

  // 表达式部分
  virtual std::any
  visitAddSubExpr(sysy2022Parser::AddSubExprContext *ctx) override {
    // 获取左操作数
    visit(ctx->expr(0));
    auto *left = valueMap.at(ctx->expr(0));
    // 获取右操作数
    visit(ctx->expr(1));
    auto *right = valueMap.at(ctx->expr(1));
    // 创建指令
    Value::Tag tag = Value::Tag::Undef;
    if (ctx->op->getText() == "+") {
      tag = Value::Tag::Add;
    } else {
      tag = Value::Tag::Sub;
    }
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any
  visitMulDivModExpr(sysy2022Parser::MulDivModExprContext *ctx) override {
    // 获取左操作数
    visit(ctx->expr(0));
    auto *left = valueMap.at(ctx->expr(0));
    // 获取右操作数
    visit(ctx->expr(1));
    auto *right = valueMap.at(ctx->expr(1));
    // 创建指令
    Value::Tag tag = Value::Tag::Undef;
    if (ctx->op->getText() == "*") {
      tag = Value::Tag::Mul;
    } else if (ctx->op->getText() == "/") {
      tag = Value::Tag::Div;
    } else {
      tag = Value::Tag::Mod;
    }
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any
  visitSubUnaryExpr(sysy2022Parser::SubUnaryExprContext *ctx) override {
    visit(ctx->unaryExpr());
    valueMap[ctx] = valueMap.at(ctx->unaryExpr());
    return {};
  }

  virtual std::any
  visitParenExpr(sysy2022Parser::ParenExprContext *ctx) override {
    visit(ctx->expr());
    valueMap[ctx] = valueMap.at(ctx->expr());
    return {};
  }

  virtual std::any
  visitLValExpr(sysy2022Parser::LValExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitIntLiteral(sysy2022Parser::IntLiteralContext *ctx) override {
    std::string intStr = ctx->getText();
    int base = 0;
    if (intStr.substr(0, 2) == "0x" || intStr.substr(0, 2) == "0X") {
      base = 16;
    } else if (intStr.substr(0, 1) == "0") {
      base = 8;
    } else {
      base = 10;
    }
    int result = std::stoi(intStr.c_str(), nullptr, base);
    valueMap[ctx] = new ConstantValue(result);
    return {};
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
    valueMap[ctx] = new ConstantValue(result);
    return {};
  }

  virtual std::any
  visitFuncCall(sysy2022Parser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitRecUnaryExpr(sysy2022Parser::RecUnaryExprContext *ctx) override {
    // 获取子操作数
    visit(ctx->unaryExpr());
    // 创建指令
    if (ctx->op->getText() == "+") {
      // do nothing
      valueMap[ctx] = valueMap.at(ctx->unaryExpr());
    } else if (ctx->op->getText() == "-") {
      // -x => 0 - x
      auto *subVal = valueMap.at(ctx->unaryExpr());
      Value *result = curBasicBlock->create<BinaryInst>(
          Value::Tag::Sub, new ConstantValue(0), subVal);
      valueMap[ctx] = result;
    } else {
      // TODO: ! in cond expr
    }
    return {};
  }

  virtual std::any visitLVal(sysy2022Parser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExpr(sysy2022Parser::EqExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitBinaryExpr(sysy2022Parser::BinaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrExpr(sysy2022Parser::OrExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExpr(sysy2022Parser::RelExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndExpr(sysy2022Parser::AndExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any
  visitConstExpr(sysy2022Parser::ConstExprContext *ctx) override {
    return visitChildren(ctx);
  }
};
