
// Generated from sysy2022.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "sysy2022Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by sysy2022Parser.
 */
class  sysy2022Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by sysy2022Parser.
   */
    virtual std::any visitCompUnit(sysy2022Parser::CompUnitContext *context) = 0;

    virtual std::any visitDecl(sysy2022Parser::DeclContext *context) = 0;

    virtual std::any visitBasicType(sysy2022Parser::BasicTypeContext *context) = 0;

    virtual std::any visitConstDecl(sysy2022Parser::ConstDeclContext *context) = 0;

    virtual std::any visitConstDef(sysy2022Parser::ConstDefContext *context) = 0;

    virtual std::any visitConstInitVal(sysy2022Parser::ConstInitValContext *context) = 0;

    virtual std::any visitVarDecl(sysy2022Parser::VarDeclContext *context) = 0;

    virtual std::any visitVarDef(sysy2022Parser::VarDefContext *context) = 0;

    virtual std::any visitInitVal(sysy2022Parser::InitValContext *context) = 0;

    virtual std::any visitFuncDef(sysy2022Parser::FuncDefContext *context) = 0;

    virtual std::any visitFuncType(sysy2022Parser::FuncTypeContext *context) = 0;

    virtual std::any visitFuncFParams(sysy2022Parser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(sysy2022Parser::FuncFParamContext *context) = 0;

    virtual std::any visitBlock(sysy2022Parser::BlockContext *context) = 0;

    virtual std::any visitBlockItem(sysy2022Parser::BlockItemContext *context) = 0;

    virtual std::any visitAssignStmt(sysy2022Parser::AssignStmtContext *context) = 0;

    virtual std::any visitExprStmt(sysy2022Parser::ExprStmtContext *context) = 0;

    virtual std::any visitBlockStmt(sysy2022Parser::BlockStmtContext *context) = 0;

    virtual std::any visitIfStmt(sysy2022Parser::IfStmtContext *context) = 0;

    virtual std::any visitWhileStmt(sysy2022Parser::WhileStmtContext *context) = 0;

    virtual std::any visitBreakStmt(sysy2022Parser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(sysy2022Parser::ContinueStmtContext *context) = 0;

    virtual std::any visitReturnStmt(sysy2022Parser::ReturnStmtContext *context) = 0;

    virtual std::any visitExpr(sysy2022Parser::ExprContext *context) = 0;

    virtual std::any visitUnaryExpr(sysy2022Parser::UnaryExprContext *context) = 0;

    virtual std::any visitUnaryOp(sysy2022Parser::UnaryOpContext *context) = 0;

    virtual std::any visitFuncRParams(sysy2022Parser::FuncRParamsContext *context) = 0;

    virtual std::any visitPrimaryExpr(sysy2022Parser::PrimaryExprContext *context) = 0;

    virtual std::any visitLVal(sysy2022Parser::LValContext *context) = 0;

    virtual std::any visitNumber(sysy2022Parser::NumberContext *context) = 0;

    virtual std::any visitCond(sysy2022Parser::CondContext *context) = 0;

    virtual std::any visitConstExpr(sysy2022Parser::ConstExprContext *context) = 0;


};

