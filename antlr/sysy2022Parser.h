
// Generated from sysy2022.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  sysy2022Parser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, ID = 34, INT = 35, FLOAT = 36, BlockComment = 37, LineComment = 38, 
    Blank = 39
  };

  enum {
    RuleCompUnit = 0, RuleDecl = 1, RuleConstDecl = 2, RuleConstDef = 3, 
    RuleConstInitVal = 4, RuleVarDecl = 5, RuleVarDef = 6, RuleInitVal = 7, 
    RuleFuncDef = 8, RuleFuncFParams = 9, RuleFuncFParam = 10, RuleBlock = 11, 
    RuleBlockItem = 12, RuleStmt = 13, RuleExpr = 14, RuleAddExpr = 15, 
    RuleMulExpr = 16, RuleUnaryExpr = 17, RuleUnaryOp = 18, RuleFuncRParams = 19, 
    RulePrimaryExpr = 20, RuleLVal = 21, RuleNumber = 22, RuleCond = 23, 
    RuleLOrExpr = 24, RuleLAndExpr = 25, RuleEqExpr = 26, RuleRelExpr = 27, 
    RuleConstExpr = 28
  };

  explicit sysy2022Parser(antlr4::TokenStream *input);

  sysy2022Parser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~sysy2022Parser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class CompUnitContext;
  class DeclContext;
  class ConstDeclContext;
  class ConstDefContext;
  class ConstInitValContext;
  class VarDeclContext;
  class VarDefContext;
  class InitValContext;
  class FuncDefContext;
  class FuncFParamsContext;
  class FuncFParamContext;
  class BlockContext;
  class BlockItemContext;
  class StmtContext;
  class ExprContext;
  class AddExprContext;
  class MulExprContext;
  class UnaryExprContext;
  class UnaryOpContext;
  class FuncRParamsContext;
  class PrimaryExprContext;
  class LValContext;
  class NumberContext;
  class CondContext;
  class LOrExprContext;
  class LAndExprContext;
  class EqExprContext;
  class RelExprContext;
  class ConstExprContext; 

  class  CompUnitContext : public antlr4::ParserRuleContext {
  public:
    CompUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<DeclContext *> decl();
    DeclContext* decl(size_t i);
    std::vector<FuncDefContext *> funcDef();
    FuncDefContext* funcDef(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompUnitContext* compUnit();

  class  DeclContext : public antlr4::ParserRuleContext {
  public:
    DeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclContext *constDecl();
    VarDeclContext *varDecl();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclContext* decl();

  class  ConstDeclContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConstDefContext *> constDef();
    ConstDefContext* constDef(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDeclContext* constDecl();

  class  ConstDefContext : public antlr4::ParserRuleContext {
  public:
    ConstDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    ConstInitValContext *constInitVal();
    std::vector<ConstExprContext *> constExpr();
    ConstExprContext* constExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDefContext* constDef();

  class  ConstInitValContext : public antlr4::ParserRuleContext {
  public:
    ConstInitValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstExprContext *constExpr();
    std::vector<ConstInitValContext *> constInitVal();
    ConstInitValContext* constInitVal(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstInitValContext* constInitVal();

  class  VarDeclContext : public antlr4::ParserRuleContext {
  public:
    VarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VarDefContext *> varDef();
    VarDefContext* varDef(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclContext* varDecl();

  class  VarDefContext : public antlr4::ParserRuleContext {
  public:
    VarDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    InitValContext *initVal();
    std::vector<ConstExprContext *> constExpr();
    ConstExprContext* constExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDefContext* varDef();

  class  InitValContext : public antlr4::ParserRuleContext {
  public:
    InitValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    std::vector<InitValContext *> initVal();
    InitValContext* initVal(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InitValContext* initVal();

  class  FuncDefContext : public antlr4::ParserRuleContext {
  public:
    FuncDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    BlockContext *block();
    FuncFParamsContext *funcFParams();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncDefContext* funcDef();

  class  FuncFParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncFParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<FuncFParamContext *> funcFParam();
    FuncFParamContext* funcFParam(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncFParamsContext* funcFParams();

  class  FuncFParamContext : public antlr4::ParserRuleContext {
  public:
    FuncFParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncFParamContext* funcFParam();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<BlockItemContext *> blockItem();
    BlockItemContext* blockItem(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  BlockItemContext : public antlr4::ParserRuleContext {
  public:
    BlockItemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclContext *decl();
    StmtContext *stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockItemContext* blockItem();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LValContext *lVal();
    ExprContext *expr();
    BlockContext *block();
    CondContext *cond();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmtContext* stmt();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddExprContext *addExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  AddExprContext : public antlr4::ParserRuleContext {
  public:
    AddExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MulExprContext *> mulExpr();
    MulExprContext* mulExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddExprContext* addExpr();

  class  MulExprContext : public antlr4::ParserRuleContext {
  public:
    MulExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExprContext *> unaryExpr();
    UnaryExprContext* unaryExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MulExprContext* mulExpr();

  class  UnaryExprContext : public antlr4::ParserRuleContext {
  public:
    UnaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExprContext *primaryExpr();
    antlr4::tree::TerminalNode *ID();
    FuncRParamsContext *funcRParams();
    UnaryOpContext *unaryOp();
    UnaryExprContext *unaryExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExprContext* unaryExpr();

  class  UnaryOpContext : public antlr4::ParserRuleContext {
  public:
    UnaryOpContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryOpContext* unaryOp();

  class  FuncRParamsContext : public antlr4::ParserRuleContext {
  public:
    FuncRParamsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncRParamsContext* funcRParams();

  class  PrimaryExprContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    LValContext *lVal();
    NumberContext *number();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExprContext* primaryExpr();

  class  LValContext : public antlr4::ParserRuleContext {
  public:
    LValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LValContext* lVal();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *FLOAT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumberContext* number();

  class  CondContext : public antlr4::ParserRuleContext {
  public:
    CondContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LOrExprContext *lOrExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CondContext* cond();

  class  LOrExprContext : public antlr4::ParserRuleContext {
  public:
    LOrExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LAndExprContext *> lAndExpr();
    LAndExprContext* lAndExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LOrExprContext* lOrExpr();

  class  LAndExprContext : public antlr4::ParserRuleContext {
  public:
    LAndExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqExprContext *> eqExpr();
    EqExprContext* eqExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LAndExprContext* lAndExpr();

  class  EqExprContext : public antlr4::ParserRuleContext {
  public:
    EqExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelExprContext *> relExpr();
    RelExprContext* relExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqExprContext* eqExpr();

  class  RelExprContext : public antlr4::ParserRuleContext {
  public:
    RelExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AddExprContext *> addExpr();
    AddExprContext* addExpr(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelExprContext* relExpr();

  class  ConstExprContext : public antlr4::ParserRuleContext {
  public:
    ConstExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AddExprContext *addExpr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstExprContext* constExpr();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

