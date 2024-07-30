
#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include <antlr4-runtime.h>
#include <sysy2022BaseVisitor.h>

#include <olc/ir/IR.h>
#include <olc/utils/symtab.h>

#include <olc/debug.h>
#include <olc/frontend/ConstFolder.h>

using namespace olc;

class ConstFoldVisitor;

class CodeGenASTVisitor : public sysy2022BaseVisitor {
  // 符号表
  SymTab<std::string, Value *> &symbolTable;
  // IR Value 表
  std::map<antlr4::ParserRuleContext *, Value *> valueMap;
  // 推导节点是否为左值
  std::map<antlr4::ParserRuleContext *, bool> isLValueMap;
  // 当前模块
  Module *curModule;
  // 当前函数
  Function *curFunction;
  // 当前基本块
  BasicBlock *curBasicBlock;

  ConstFoldVisitor &constFolder;

  // 标签计数
  int labelCnt;
  // 当前条件块(for continue) 当前结束块(for break)
  BasicBlock *curCondBB, *curEndBB;

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

  Value *createLValue(antlr4::ParserRuleContext *ctx) {
    visit(ctx);
    assert(isLValueMap[ctx] && "not a lvalue");
    return valueMap.at(ctx);
  }

  Value *createRValue(antlr4::ParserRuleContext *ctx) {
    visit(ctx);
    if (isLValueMap[ctx]) {
      return curBasicBlock->create<LoadInst>(valueMap.at(ctx));
    }
    return valueMap.at(ctx);
  }

public:
  CodeGenASTVisitor(
      Module *module, ConstFoldVisitor &constFolder,
      SymTab<std::string, Value *> &symbolTable)
      : curModule(module), curFunction(nullptr), constFolder(constFolder),
        symbolTable(symbolTable), labelCnt(0) {}

  virtual std::any
  visitCompUnit(sysy2022Parser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  //--------------------------------------------------------------------------
  // 声明部分
  //--------------------------------------------------------------------------
  virtual std::any visitVarDecl(sysy2022Parser::VarDeclContext *ctx) override {
    Type *type = convertType(ctx->basicType->getText());
    bool isGlobal = (curFunction == nullptr); // 检查是否在全局作用域中

    for (const auto &varDef : ctx->varDef()) {
      std::string varName = varDef->ID()->getText();
      if (varDef->constExpr().size() > 0) {
        size_t size = 1;
        std::vector<int> dimSizes;
        for (const auto &expr : varDef->constExpr()) {
          int d =
              std::any_cast<ConstantValue *>(constFolder.visit(expr))->getInt();
          size *= d;
          dimSizes.push_back(d);
        }
        Type *arrayType = ArrayType::get(type, size, dimSizes);
        if (isGlobal) {
          olc_unreachable("NYI");
        } else {
          // 局部变量分配
          Value *allocaInst = curBasicBlock->create<AllocaInst>(arrayType);
          symbolTable.insert(varName, allocaInst);
          // 处理初始化表达式（如果有）
          if (varDef->initVal()) {
            Value *initVal = createRValue(varDef->initVal());
            curBasicBlock->create<StoreInst>(initVal, allocaInst);
          }
        }
      } else {
        if (isGlobal) {
          // 初始化全局变量的值
          Constant *initializer = nullptr;
          if (varDef->initVal()) {
            initializer = std::any_cast<ConstantValue *>(
                constFolder.visit(varDef->initVal()));
            // 判断全局变量是否为常量
          }
          GlobalVariable *globalVar =
              new GlobalVariable(type, varName, initializer);
          curModule->addGlobal(globalVar);
          symbolTable.insert(varName, globalVar);
        } else {
          // 局部变量分配
          Value *allocaInst = curBasicBlock->create<AllocaInst>(type);
          symbolTable.insert(varName, allocaInst);
          // 处理初始化表达式（如果有）
          if (varDef->initVal()) {
            Value *initVal = createRValue(varDef->initVal());
            curBasicBlock->create<StoreInst>(initVal, allocaInst);
          }
        }
      }
    }
    return {};
  }

  virtual std::any visitVarDef(sysy2022Parser::VarDefContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  virtual std::any visitInitVal(sysy2022Parser::InitValContext *ctx) override {
    if (ctx->expr()) {
      valueMap[ctx] = createRValue(ctx->expr());
    } else {
      // TODO: 处理初始化列表
      std::vector<Value *> initValues;
      for (const auto &initVal : ctx->initVal()) {
        visit(initVal);
        initValues.push_back(valueMap.at(initVal));
        // ...
      }
      // valueMap[ctx] =
      olc_unreachable("NYI");
    }
    return {};
  }

  //--------------------------------------------------------------------------
  // 函数部分
  //--------------------------------------------------------------------------
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

    // 函数名加到顶层符号表
    symbolTable.insert(ctx->ID()->getText(), function);

    // 进入新的作用域
    symbolTable.enterScope();
    // 参数加到符号表中 生成alloca和store指令
    for (const auto &arg : args) {
      Value *allocaInst = curBasicBlock->create<AllocaInst>(arg->getType());
      curBasicBlock->create<StoreInst>(arg, allocaInst);
      symbolTable.insert(arg->argName, allocaInst);
    }

    // 处理函数体
    visit(ctx->block());

    // void函数 增加ret指令
    if (retType->isVoidTy() &&
        (curBasicBlock->instructions.size() == 0 ||
         !isa<ReturnInst>(curBasicBlock->instructions.back()))) {
      curBasicBlock->create<ReturnInst>();
    }

    // 退出作用域
    symbolTable.exitScope();

    curFunction = nullptr;
    curBasicBlock = nullptr;

    return {};
  }

  virtual std::any
  visitFuncFParam(sysy2022Parser::FuncFParamContext *ctx) override {
    olc_unreachable("Never");
    return {};
  }

  //--------------------------------------------------------------------------
  // 语句部分
  //--------------------------------------------------------------------------
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
    // 获取右值
    auto *rVal = createRValue(ctx->expr());
    // 创建指令
    auto *lVal = createLValue(ctx->lVal());
    curBasicBlock->create<StoreInst>(rVal, lVal);
    return {};
  }

  virtual std::any
  visitExprStmt(sysy2022Parser::ExprStmtContext *ctx) override {
    visit(ctx->expr());
    return {};
  }

  virtual std::any
  visitBlockStmt(sysy2022Parser::BlockStmtContext *ctx) override {
    visit(ctx->block());
    return {};
  }

  virtual std::any visitIfStmt(sysy2022Parser::IfStmtContext *ctx) override {
    // 获取条件
    auto *condInst = createRValue(ctx->cond());
    // 创建基本块
    BasicBlock *btrue = nullptr, *bfalse = nullptr, *end = nullptr;
    btrue = new BasicBlock(curFunction, "btrue" + std::to_string(labelCnt++));
    if (ctx->stmt().size() == 2) {
      bfalse =
          new BasicBlock(curFunction, "bfalse" + std::to_string(labelCnt++));
    }
    end = new BasicBlock(curFunction, "endif" + std::to_string(labelCnt++));

    btrue->predecessors.push_back(curBasicBlock);
    curBasicBlock->successors.push_back(btrue);

    if (bfalse) {
      bfalse->predecessors.push_back(curBasicBlock);
      bfalse->successors.push_back(end);
    }

    end->predecessors.push_back(btrue);
    btrue->successors.push_back(end);

    end->predecessors.push_back(bfalse ? bfalse : curBasicBlock);
    curBasicBlock->successors.push_back(bfalse ? bfalse : end);

    // 创建指令
    curBasicBlock->create<BranchInst>(condInst, btrue, bfalse ? bfalse : end);

    // btrue
    curFunction->addBasicBlock(btrue);
    curBasicBlock = btrue;
    visit(ctx->stmt(0));
    curBasicBlock->create<JumpInst>(end);

    // bfalse
    if (ctx->stmt().size() == 2) {
      curFunction->addBasicBlock(bfalse);
      curBasicBlock = bfalse;
      visit(ctx->stmt(1));
      curBasicBlock->create<JumpInst>(end);
    }

    // end
    curFunction->addBasicBlock(end);
    curBasicBlock = end;

    return {};
  }

  virtual std::any
  visitWhileStmt(sysy2022Parser::WhileStmtContext *ctx) override {
    // 创建基本块
    BasicBlock *cond = nullptr, *loop = nullptr, *end = nullptr;
    cond = new BasicBlock(curFunction, "cond" + std::to_string(labelCnt++));
    loop = new BasicBlock(curFunction, "loop" + std::to_string(labelCnt++));
    end = new BasicBlock(curFunction, "endloop" + std::to_string(labelCnt++));
    curCondBB = cond;
    curEndBB = end;

    cond->predecessors.push_back(curBasicBlock);
    curBasicBlock->successors.push_back(cond);

    loop->predecessors.push_back(cond);
    cond->successors.push_back(loop);

    end->predecessors.push_back(cond);
    cond->successors.push_back(end);

    cond->predecessors.push_back(loop);
    loop->successors.push_back(cond);

    // 创建指令
    curBasicBlock->create<JumpInst>(cond);

    // cond
    curFunction->addBasicBlock(cond);
    curBasicBlock = cond;
    // 获取条件
    auto *condInst = createRValue(ctx->cond());
    // 创建指令
    curBasicBlock->create<BranchInst>(condInst, loop, end);

    // loop
    curFunction->addBasicBlock(loop);
    curBasicBlock = loop;
    visit(ctx->stmt());
    curBasicBlock->create<JumpInst>(cond);

    // end
    curFunction->addBasicBlock(end);
    curBasicBlock = end;

    return {};
  }

  virtual std::any
  visitBreakStmt(sysy2022Parser::BreakStmtContext *ctx) override {
    curBasicBlock->create<JumpInst>(curEndBB);
    if (find(
            curEndBB->predecessors.begin(), curEndBB->predecessors.end(),
            curBasicBlock) == curEndBB->predecessors.end()) {
      curEndBB->predecessors.push_back(curBasicBlock);
      curBasicBlock->successors.push_back(curEndBB);
    }
    return {};
  }

  virtual std::any
  visitContinueStmt(sysy2022Parser::ContinueStmtContext *ctx) override {
    curBasicBlock->create<JumpInst>(curCondBB);
    if (find(
            curCondBB->predecessors.begin(), curCondBB->predecessors.end(),
            curBasicBlock) == curCondBB->predecessors.end()) {
      curCondBB->predecessors.push_back(curBasicBlock);
      curBasicBlock->successors.push_back(curCondBB);
    }
    return {};
  }

  virtual std::any
  visitReturnStmt(sysy2022Parser::ReturnStmtContext *ctx) override {
    if (ctx->expr()) {
      // 获取子操作数
      auto *retVal = createRValue(ctx->expr());
      // 创建指令
      Value *result = curBasicBlock->create<ReturnInst>(retVal);
    } else {
      Value *result = curBasicBlock->create<ReturnInst>();
    }
    return {};
  }

  //--------------------------------------------------------------------------
  // 表达式部分
  //--------------------------------------------------------------------------
  virtual std::any
  visitAddSubExpr(sysy2022Parser::AddSubExprContext *ctx) override {
    // TODO: 类型转换
    // 获取左操作数
    auto *left = createRValue(ctx->expr(0));
    // 获取右操作数
    auto *right = createRValue(ctx->expr(1));
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
    auto *left = createRValue(ctx->expr(0));
    // 获取右操作数
    auto *right = createRValue(ctx->expr(1));
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
    valueMap[ctx] = createRValue(ctx->unaryExpr());
    return {};
  }

  virtual std::any
  visitParenExpr(sysy2022Parser::ParenExprContext *ctx) override {
    visit(ctx->expr());
    valueMap[ctx] = valueMap.at(ctx->expr());
    isLValueMap[ctx] = isLValueMap[ctx->expr()];
    return {};
  }

  virtual std::any
  visitLValExpr(sysy2022Parser::LValExprContext *ctx) override {
    visit(ctx->lVal());
    valueMap[ctx] = valueMap.at(ctx->lVal());
    isLValueMap[ctx] = isLValueMap[ctx->lVal()];
    return {};
  }

  virtual std::any
  visitIntLiteral(sysy2022Parser::IntLiteralContext *ctx) override {
    std::string intStr = ctx->getText();
    int result = std::stoi(intStr.c_str(), nullptr, 0);
    valueMap[ctx] = new ConstantValue(result);
    return {};
  }

  virtual std::any
  visitFloatLiteral(sysy2022Parser::FloatLiteralContext *ctx) override {
    std::string floatStr = ctx->getText();
    float result = std::stof(floatStr.c_str());
    valueMap[ctx] = new ConstantValue(result);
    return {};
  }

  virtual std::any
  visitFuncCall(sysy2022Parser::FuncCallContext *ctx) override {
    auto *callee = cast<Function>(symbolTable.lookup(ctx->ID()->getText()));
    std::vector<Value *> args;
    // 处理实参
    for (const auto &argCtx : ctx->expr()) {
      auto *arg = createRValue(argCtx);
      args.push_back(arg);
    }
    auto *callInst = curBasicBlock->create<CallInst>(callee, args);
    valueMap[ctx] = callInst;
    return {};
  }

  virtual std::any
  visitRecUnaryExpr(sysy2022Parser::RecUnaryExprContext *ctx) override {
    // 创建指令
    if (ctx->op->getText() == "+") {
      // do nothing
      valueMap[ctx] = createRValue(ctx->unaryExpr());
    } else if (ctx->op->getText() == "-") {
      // -x => 0 - x
      auto *subVal = createRValue(ctx->unaryExpr());
      Value *result = curBasicBlock->create<BinaryInst>(
          Value::Tag::Sub, new ConstantValue(0), subVal);
      valueMap[ctx] = result;
    } else {
      auto *subVal = createRValue(ctx->unaryExpr());
      Value *result = curBasicBlock->create<BinaryInst>(
          Value::Tag::Eq, subVal, new ConstantValue(0));
      valueMap[ctx] = result;
    }
    return {};
  }

  virtual std::any visitLVal(sysy2022Parser::LValContext *ctx) override {
    if (ctx->expr().size()) {
      // TODO: 数组
      olc_unreachable("NYI");
    }
    auto *lVal = symbolTable.lookup(ctx->ID()->getText());
    if (!lVal) {
      fprintf(stderr, "undefined variable: %s\n", ctx->ID()->getText().c_str());
      olc_unreachable("error");
    }
    valueMap[ctx] = lVal;
    isLValueMap[ctx] = true;
    return {};
  }

  virtual std::any visitEqExpr(sysy2022Parser::EqExprContext *ctx) override {
    // 获取左操作数
    auto *left = createRValue(ctx->cond(0));
    // 获取右操作数
    auto *right = createRValue(ctx->cond(1));
    // 创建指令
    Value::Tag tag = Value::Tag::Undef;
    if (ctx->op->getText() == "==") {
      tag = Value::Tag::Eq;
    } else {
      tag = Value::Tag::Ne;
    }
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any
  visitBinaryExpr(sysy2022Parser::BinaryExprContext *ctx) override {
    valueMap[ctx] = createRValue(ctx->expr());
    return {};
  }

  virtual std::any visitOrExpr(sysy2022Parser::OrExprContext *ctx) override {
    // 获取左操作数
    auto *left = createRValue(ctx->cond(0));
    // 获取右操作数
    auto *right = createRValue(ctx->cond(1));
    // 创建指令
    Value::Tag tag = Value::Tag::Or;
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any visitRelExpr(sysy2022Parser::RelExprContext *ctx) override {
    // 获取左操作数
    auto *left = createRValue(ctx->cond(0));
    // 获取右操作数
    auto *right = createRValue(ctx->cond(1));
    // 创建指令
    Value::Tag tag = Value::Tag::Undef;
    if (ctx->op->getText() == "<") {
      tag = Value::Tag::Lt;
    } else if (ctx->op->getText() == ">") {
      tag = Value::Tag::Gt;
    } else if (ctx->op->getText() == "<=") {
      tag = Value::Tag::Le;
    } else {
      tag = Value::Tag::Ge;
    }
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any visitAndExpr(sysy2022Parser::AndExprContext *ctx) override {
    // 获取左操作数
    auto *left = createRValue(ctx->cond(0));
    // 获取右操作数
    auto *right = createRValue(ctx->cond(1));
    // 创建指令
    Value::Tag tag = Value::Tag::And;
    Value *result = curBasicBlock->create<BinaryInst>(tag, left, right);
    // 返回值
    valueMap[ctx] = result;
    return {};
  }

  virtual std::any
  visitConstExpr(sysy2022Parser::ConstExprContext *ctx) override {
    valueMap[ctx] = createRValue(ctx->expr());
    return {};
  }
};
