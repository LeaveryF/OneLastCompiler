
// Generated from sysy2022.g4 by ANTLR 4.13.1


#include "sysy2022Visitor.h"

#include "sysy2022Parser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct Sysy2022ParserStaticData final {
  Sysy2022ParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Sysy2022ParserStaticData(const Sysy2022ParserStaticData&) = delete;
  Sysy2022ParserStaticData(Sysy2022ParserStaticData&&) = delete;
  Sysy2022ParserStaticData& operator=(const Sysy2022ParserStaticData&) = delete;
  Sysy2022ParserStaticData& operator=(Sysy2022ParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysy2022ParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
Sysy2022ParserStaticData *sysy2022ParserStaticData = nullptr;

void sysy2022ParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sysy2022ParserStaticData != nullptr) {
    return;
  }
#else
  assert(sysy2022ParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<Sysy2022ParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "constDecl", "constDef", "constInitVal", "varDecl", 
      "varDef", "initVal", "funcDef", "funcFParam", "block", "stmt", "expr", 
      "unaryExpr", "lVal", "cond", "constExpr"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'float'", "','", "';'", "'['", "']'", "'='", 
      "'{'", "'}'", "'void'", "'('", "')'", "'if'", "'else'", "'while'", 
      "'break'", "'continue'", "'return'", "'*'", "'/'", "'%'", "'+'", "'-'", 
      "'!'", "'<'", "'>'", "'<='", "'>='", "'=='", "'!='", "'&&'", "'||'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "ID", "INT", "FLOAT", "BlockComment", "LineComment", "Blank"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,279,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,5,0,37,8,0,10,0,12,0,40,9,0,1,0,1,0,1,
  	1,1,1,3,1,46,8,1,1,2,1,2,1,2,1,2,1,2,5,2,53,8,2,10,2,12,2,56,9,2,1,2,
  	1,2,1,3,1,3,1,3,1,3,1,3,5,3,65,8,3,10,3,12,3,68,9,3,1,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,4,5,4,78,8,4,10,4,12,4,81,9,4,3,4,83,8,4,1,4,3,4,86,8,4,1,
  	5,1,5,1,5,1,5,5,5,92,8,5,10,5,12,5,95,9,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	5,6,104,8,6,10,6,12,6,107,9,6,1,6,1,6,3,6,111,8,6,1,7,1,7,1,7,1,7,1,7,
  	5,7,118,8,7,10,7,12,7,121,9,7,3,7,123,8,7,1,7,3,7,126,8,7,1,8,1,8,1,8,
  	1,8,1,8,1,8,5,8,134,8,8,10,8,12,8,137,9,8,3,8,139,8,8,1,8,1,8,1,8,1,9,
  	1,9,1,9,1,9,1,9,1,9,5,9,150,8,9,10,9,12,9,153,9,9,1,9,5,9,156,8,9,10,
  	9,12,9,159,9,9,3,9,161,8,9,1,10,1,10,1,10,5,10,166,8,10,10,10,12,10,169,
  	9,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,3,11,179,8,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,190,8,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,204,8,11,1,11,3,11,207,8,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,218,8,12,10,12,12,
  	12,221,9,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,5,13,235,8,13,10,13,12,13,238,9,13,3,13,240,8,13,1,13,1,13,1,13,3,
  	13,245,8,13,1,14,1,14,1,14,1,14,1,14,5,14,252,8,14,10,14,12,14,255,9,
  	14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,5,15,272,8,15,10,15,12,15,275,9,15,1,16,1,16,1,16,0,2,24,30,17,
  	0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,7,1,0,2,3,2,0,2,3,11,
  	11,1,0,20,22,1,0,23,24,1,0,23,25,1,0,26,29,1,0,30,31,306,0,38,1,0,0,0,
  	2,45,1,0,0,0,4,47,1,0,0,0,6,59,1,0,0,0,8,85,1,0,0,0,10,87,1,0,0,0,12,
  	98,1,0,0,0,14,125,1,0,0,0,16,127,1,0,0,0,18,143,1,0,0,0,20,162,1,0,0,
  	0,22,206,1,0,0,0,24,208,1,0,0,0,26,244,1,0,0,0,28,246,1,0,0,0,30,256,
  	1,0,0,0,32,276,1,0,0,0,34,37,3,2,1,0,35,37,3,16,8,0,36,34,1,0,0,0,36,
  	35,1,0,0,0,37,40,1,0,0,0,38,36,1,0,0,0,38,39,1,0,0,0,39,41,1,0,0,0,40,
  	38,1,0,0,0,41,42,5,0,0,1,42,1,1,0,0,0,43,46,3,4,2,0,44,46,3,10,5,0,45,
  	43,1,0,0,0,45,44,1,0,0,0,46,3,1,0,0,0,47,48,5,1,0,0,48,49,7,0,0,0,49,
  	54,3,6,3,0,50,51,5,4,0,0,51,53,3,6,3,0,52,50,1,0,0,0,53,56,1,0,0,0,54,
  	52,1,0,0,0,54,55,1,0,0,0,55,57,1,0,0,0,56,54,1,0,0,0,57,58,5,5,0,0,58,
  	5,1,0,0,0,59,66,5,34,0,0,60,61,5,6,0,0,61,62,3,32,16,0,62,63,5,7,0,0,
  	63,65,1,0,0,0,64,60,1,0,0,0,65,68,1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,
  	67,69,1,0,0,0,68,66,1,0,0,0,69,70,5,8,0,0,70,71,3,8,4,0,71,7,1,0,0,0,
  	72,86,3,32,16,0,73,82,5,9,0,0,74,79,3,8,4,0,75,76,5,4,0,0,76,78,3,8,4,
  	0,77,75,1,0,0,0,78,81,1,0,0,0,79,77,1,0,0,0,79,80,1,0,0,0,80,83,1,0,0,
  	0,81,79,1,0,0,0,82,74,1,0,0,0,82,83,1,0,0,0,83,84,1,0,0,0,84,86,5,10,
  	0,0,85,72,1,0,0,0,85,73,1,0,0,0,86,9,1,0,0,0,87,88,7,0,0,0,88,93,3,12,
  	6,0,89,90,5,4,0,0,90,92,3,12,6,0,91,89,1,0,0,0,92,95,1,0,0,0,93,91,1,
  	0,0,0,93,94,1,0,0,0,94,96,1,0,0,0,95,93,1,0,0,0,96,97,5,5,0,0,97,11,1,
  	0,0,0,98,105,5,34,0,0,99,100,5,6,0,0,100,101,3,32,16,0,101,102,5,7,0,
  	0,102,104,1,0,0,0,103,99,1,0,0,0,104,107,1,0,0,0,105,103,1,0,0,0,105,
  	106,1,0,0,0,106,110,1,0,0,0,107,105,1,0,0,0,108,109,5,8,0,0,109,111,3,
  	14,7,0,110,108,1,0,0,0,110,111,1,0,0,0,111,13,1,0,0,0,112,126,3,24,12,
  	0,113,122,5,9,0,0,114,119,3,14,7,0,115,116,5,4,0,0,116,118,3,14,7,0,117,
  	115,1,0,0,0,118,121,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,123,1,
  	0,0,0,121,119,1,0,0,0,122,114,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,
  	124,126,5,10,0,0,125,112,1,0,0,0,125,113,1,0,0,0,126,15,1,0,0,0,127,128,
  	7,1,0,0,128,129,5,34,0,0,129,138,5,12,0,0,130,135,3,18,9,0,131,132,5,
  	4,0,0,132,134,3,18,9,0,133,131,1,0,0,0,134,137,1,0,0,0,135,133,1,0,0,
  	0,135,136,1,0,0,0,136,139,1,0,0,0,137,135,1,0,0,0,138,130,1,0,0,0,138,
  	139,1,0,0,0,139,140,1,0,0,0,140,141,5,13,0,0,141,142,3,20,10,0,142,17,
  	1,0,0,0,143,144,7,0,0,0,144,160,5,34,0,0,145,146,5,6,0,0,146,157,5,7,
  	0,0,147,151,5,6,0,0,148,150,3,24,12,0,149,148,1,0,0,0,150,153,1,0,0,0,
  	151,149,1,0,0,0,151,152,1,0,0,0,152,154,1,0,0,0,153,151,1,0,0,0,154,156,
  	5,7,0,0,155,147,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,
  	0,158,161,1,0,0,0,159,157,1,0,0,0,160,145,1,0,0,0,160,161,1,0,0,0,161,
  	19,1,0,0,0,162,167,5,9,0,0,163,166,3,2,1,0,164,166,3,22,11,0,165,163,
  	1,0,0,0,165,164,1,0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,168,1,0,0,
  	0,168,170,1,0,0,0,169,167,1,0,0,0,170,171,5,10,0,0,171,21,1,0,0,0,172,
  	173,3,28,14,0,173,174,5,8,0,0,174,175,3,24,12,0,175,176,5,5,0,0,176,207,
  	1,0,0,0,177,179,3,24,12,0,178,177,1,0,0,0,178,179,1,0,0,0,179,180,1,0,
  	0,0,180,207,5,5,0,0,181,207,3,20,10,0,182,183,5,14,0,0,183,184,5,12,0,
  	0,184,185,3,30,15,0,185,186,5,13,0,0,186,189,3,22,11,0,187,188,5,15,0,
  	0,188,190,3,22,11,0,189,187,1,0,0,0,189,190,1,0,0,0,190,207,1,0,0,0,191,
  	192,5,16,0,0,192,193,5,12,0,0,193,194,3,30,15,0,194,195,5,13,0,0,195,
  	196,3,22,11,0,196,207,1,0,0,0,197,198,5,17,0,0,198,207,5,5,0,0,199,200,
  	5,18,0,0,200,207,5,5,0,0,201,203,5,19,0,0,202,204,3,24,12,0,203,202,1,
  	0,0,0,203,204,1,0,0,0,204,205,1,0,0,0,205,207,5,5,0,0,206,172,1,0,0,0,
  	206,178,1,0,0,0,206,181,1,0,0,0,206,182,1,0,0,0,206,191,1,0,0,0,206,197,
  	1,0,0,0,206,199,1,0,0,0,206,201,1,0,0,0,207,23,1,0,0,0,208,209,6,12,-1,
  	0,209,210,3,26,13,0,210,219,1,0,0,0,211,212,10,2,0,0,212,213,7,2,0,0,
  	213,218,3,24,12,3,214,215,10,1,0,0,215,216,7,3,0,0,216,218,3,24,12,2,
  	217,211,1,0,0,0,217,214,1,0,0,0,218,221,1,0,0,0,219,217,1,0,0,0,219,220,
  	1,0,0,0,220,25,1,0,0,0,221,219,1,0,0,0,222,223,5,12,0,0,223,224,3,24,
  	12,0,224,225,5,13,0,0,225,245,1,0,0,0,226,245,3,28,14,0,227,245,5,35,
  	0,0,228,245,5,36,0,0,229,230,5,34,0,0,230,239,5,12,0,0,231,236,3,24,12,
  	0,232,233,5,4,0,0,233,235,3,24,12,0,234,232,1,0,0,0,235,238,1,0,0,0,236,
  	234,1,0,0,0,236,237,1,0,0,0,237,240,1,0,0,0,238,236,1,0,0,0,239,231,1,
  	0,0,0,239,240,1,0,0,0,240,241,1,0,0,0,241,245,5,13,0,0,242,243,7,4,0,
  	0,243,245,3,26,13,0,244,222,1,0,0,0,244,226,1,0,0,0,244,227,1,0,0,0,244,
  	228,1,0,0,0,244,229,1,0,0,0,244,242,1,0,0,0,245,27,1,0,0,0,246,253,5,
  	34,0,0,247,248,5,6,0,0,248,249,3,24,12,0,249,250,5,7,0,0,250,252,1,0,
  	0,0,251,247,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,253,254,1,0,0,0,254,
  	29,1,0,0,0,255,253,1,0,0,0,256,257,6,15,-1,0,257,258,3,24,12,0,258,273,
  	1,0,0,0,259,260,10,4,0,0,260,261,7,5,0,0,261,272,3,30,15,5,262,263,10,
  	3,0,0,263,264,7,6,0,0,264,272,3,30,15,4,265,266,10,2,0,0,266,267,5,32,
  	0,0,267,272,3,30,15,3,268,269,10,1,0,0,269,270,5,33,0,0,270,272,3,30,
  	15,2,271,259,1,0,0,0,271,262,1,0,0,0,271,265,1,0,0,0,271,268,1,0,0,0,
  	272,275,1,0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,274,31,1,0,0,0,275,273,
  	1,0,0,0,276,277,3,24,12,0,277,33,1,0,0,0,33,36,38,45,54,66,79,82,85,93,
  	105,110,119,122,125,135,138,151,157,160,165,167,178,189,203,206,217,219,
  	236,239,244,253,271,273
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysy2022ParserStaticData = staticData.release();
}

}

sysy2022Parser::sysy2022Parser(TokenStream *input) : sysy2022Parser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

sysy2022Parser::sysy2022Parser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  sysy2022Parser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sysy2022ParserStaticData->atn, sysy2022ParserStaticData->decisionToDFA, sysy2022ParserStaticData->sharedContextCache, options);
}

sysy2022Parser::~sysy2022Parser() {
  delete _interpreter;
}

const atn::ATN& sysy2022Parser::getATN() const {
  return *sysy2022ParserStaticData->atn;
}

std::string sysy2022Parser::getGrammarFileName() const {
  return "sysy2022.g4";
}

const std::vector<std::string>& sysy2022Parser::getRuleNames() const {
  return sysy2022ParserStaticData->ruleNames;
}

const dfa::Vocabulary& sysy2022Parser::getVocabulary() const {
  return sysy2022ParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView sysy2022Parser::getSerializedATN() const {
  return sysy2022ParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

sysy2022Parser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::CompUnitContext::EOF() {
  return getToken(sysy2022Parser::EOF, 0);
}

std::vector<sysy2022Parser::DeclContext *> sysy2022Parser::CompUnitContext::decl() {
  return getRuleContexts<sysy2022Parser::DeclContext>();
}

sysy2022Parser::DeclContext* sysy2022Parser::CompUnitContext::decl(size_t i) {
  return getRuleContext<sysy2022Parser::DeclContext>(i);
}

std::vector<sysy2022Parser::FuncDefContext *> sysy2022Parser::CompUnitContext::funcDef() {
  return getRuleContexts<sysy2022Parser::FuncDefContext>();
}

sysy2022Parser::FuncDefContext* sysy2022Parser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<sysy2022Parser::FuncDefContext>(i);
}


size_t sysy2022Parser::CompUnitContext::getRuleIndex() const {
  return sysy2022Parser::RuleCompUnit;
}


std::any sysy2022Parser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::CompUnitContext* sysy2022Parser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, sysy2022Parser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(38);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2062) != 0)) {
      setState(36);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(34);
        decl();
        break;
      }

      case 2: {
        setState(35);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(40);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(41);
    match(sysy2022Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

sysy2022Parser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::ConstDeclContext* sysy2022Parser::DeclContext::constDecl() {
  return getRuleContext<sysy2022Parser::ConstDeclContext>(0);
}

sysy2022Parser::VarDeclContext* sysy2022Parser::DeclContext::varDecl() {
  return getRuleContext<sysy2022Parser::VarDeclContext>(0);
}


size_t sysy2022Parser::DeclContext::getRuleIndex() const {
  return sysy2022Parser::RuleDecl;
}


std::any sysy2022Parser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::DeclContext* sysy2022Parser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, sysy2022Parser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(45);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__0: {
        enterOuterAlt(_localctx, 1);
        setState(43);
        constDecl();
        break;
      }

      case sysy2022Parser::T__1:
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 2);
        setState(44);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

sysy2022Parser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::ConstDefContext *> sysy2022Parser::ConstDeclContext::constDef() {
  return getRuleContexts<sysy2022Parser::ConstDefContext>();
}

sysy2022Parser::ConstDefContext* sysy2022Parser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<sysy2022Parser::ConstDefContext>(i);
}


size_t sysy2022Parser::ConstDeclContext::getRuleIndex() const {
  return sysy2022Parser::RuleConstDecl;
}


std::any sysy2022Parser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::ConstDeclContext* sysy2022Parser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, sysy2022Parser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(47);
    match(sysy2022Parser::T__0);
    setState(48);
    antlrcpp::downCast<ConstDeclContext *>(_localctx)->basicType = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
      antlrcpp::downCast<ConstDeclContext *>(_localctx)->basicType = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(49);
    constDef();
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(50);
      match(sysy2022Parser::T__3);
      setState(51);
      constDef();
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
    match(sysy2022Parser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

sysy2022Parser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::ConstDefContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

sysy2022Parser::ConstInitValContext* sysy2022Parser::ConstDefContext::constInitVal() {
  return getRuleContext<sysy2022Parser::ConstInitValContext>(0);
}

std::vector<sysy2022Parser::ConstExprContext *> sysy2022Parser::ConstDefContext::constExpr() {
  return getRuleContexts<sysy2022Parser::ConstExprContext>();
}

sysy2022Parser::ConstExprContext* sysy2022Parser::ConstDefContext::constExpr(size_t i) {
  return getRuleContext<sysy2022Parser::ConstExprContext>(i);
}


size_t sysy2022Parser::ConstDefContext::getRuleIndex() const {
  return sysy2022Parser::RuleConstDef;
}


std::any sysy2022Parser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::ConstDefContext* sysy2022Parser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 6, sysy2022Parser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(sysy2022Parser::ID);
    setState(66);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(60);
      match(sysy2022Parser::T__5);
      setState(61);
      constExpr();
      setState(62);
      match(sysy2022Parser::T__6);
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(69);
    match(sysy2022Parser::T__7);
    setState(70);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

sysy2022Parser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::ConstExprContext* sysy2022Parser::ConstInitValContext::constExpr() {
  return getRuleContext<sysy2022Parser::ConstExprContext>(0);
}

std::vector<sysy2022Parser::ConstInitValContext *> sysy2022Parser::ConstInitValContext::constInitVal() {
  return getRuleContexts<sysy2022Parser::ConstInitValContext>();
}

sysy2022Parser::ConstInitValContext* sysy2022Parser::ConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<sysy2022Parser::ConstInitValContext>(i);
}


size_t sysy2022Parser::ConstInitValContext::getRuleIndex() const {
  return sysy2022Parser::RuleConstInitVal;
}


std::any sysy2022Parser::ConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitConstInitVal(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::ConstInitValContext* sysy2022Parser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 8, sysy2022Parser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(85);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__11:
      case sysy2022Parser::T__22:
      case sysy2022Parser::T__23:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(72);
        constExpr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(73);
        match(sysy2022Parser::T__8);
        setState(82);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317809152) != 0)) {
          setState(74);
          constInitVal();
          setState(79);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(75);
            match(sysy2022Parser::T__3);
            setState(76);
            constInitVal();
            setState(81);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(84);
        match(sysy2022Parser::T__9);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

sysy2022Parser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::VarDefContext *> sysy2022Parser::VarDeclContext::varDef() {
  return getRuleContexts<sysy2022Parser::VarDefContext>();
}

sysy2022Parser::VarDefContext* sysy2022Parser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<sysy2022Parser::VarDefContext>(i);
}


size_t sysy2022Parser::VarDeclContext::getRuleIndex() const {
  return sysy2022Parser::RuleVarDecl;
}


std::any sysy2022Parser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::VarDeclContext* sysy2022Parser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 10, sysy2022Parser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    antlrcpp::downCast<VarDeclContext *>(_localctx)->basicType = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
      antlrcpp::downCast<VarDeclContext *>(_localctx)->basicType = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(88);
    varDef();
    setState(93);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(89);
      match(sysy2022Parser::T__3);
      setState(90);
      varDef();
      setState(95);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(96);
    match(sysy2022Parser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

sysy2022Parser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::VarDefContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

std::vector<sysy2022Parser::ConstExprContext *> sysy2022Parser::VarDefContext::constExpr() {
  return getRuleContexts<sysy2022Parser::ConstExprContext>();
}

sysy2022Parser::ConstExprContext* sysy2022Parser::VarDefContext::constExpr(size_t i) {
  return getRuleContext<sysy2022Parser::ConstExprContext>(i);
}

sysy2022Parser::InitValContext* sysy2022Parser::VarDefContext::initVal() {
  return getRuleContext<sysy2022Parser::InitValContext>(0);
}


size_t sysy2022Parser::VarDefContext::getRuleIndex() const {
  return sysy2022Parser::RuleVarDef;
}


std::any sysy2022Parser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::VarDefContext* sysy2022Parser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 12, sysy2022Parser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(sysy2022Parser::ID);
    setState(105);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(99);
      match(sysy2022Parser::T__5);
      setState(100);
      constExpr();
      setState(101);
      match(sysy2022Parser::T__6);
      setState(107);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__7) {
      setState(108);
      match(sysy2022Parser::T__7);
      setState(109);
      initVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

sysy2022Parser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::ExprContext* sysy2022Parser::InitValContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

std::vector<sysy2022Parser::InitValContext *> sysy2022Parser::InitValContext::initVal() {
  return getRuleContexts<sysy2022Parser::InitValContext>();
}

sysy2022Parser::InitValContext* sysy2022Parser::InitValContext::initVal(size_t i) {
  return getRuleContext<sysy2022Parser::InitValContext>(i);
}


size_t sysy2022Parser::InitValContext::getRuleIndex() const {
  return sysy2022Parser::RuleInitVal;
}


std::any sysy2022Parser::InitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitInitVal(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::InitValContext* sysy2022Parser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 14, sysy2022Parser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__11:
      case sysy2022Parser::T__22:
      case sysy2022Parser::T__23:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(112);
        expr(0);
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(113);
        match(sysy2022Parser::T__8);
        setState(122);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317809152) != 0)) {
          setState(114);
          initVal();
          setState(119);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(115);
            match(sysy2022Parser::T__3);
            setState(116);
            initVal();
            setState(121);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(124);
        match(sysy2022Parser::T__9);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

sysy2022Parser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::FuncDefContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

sysy2022Parser::BlockContext* sysy2022Parser::FuncDefContext::block() {
  return getRuleContext<sysy2022Parser::BlockContext>(0);
}

std::vector<sysy2022Parser::FuncFParamContext *> sysy2022Parser::FuncDefContext::funcFParam() {
  return getRuleContexts<sysy2022Parser::FuncFParamContext>();
}

sysy2022Parser::FuncFParamContext* sysy2022Parser::FuncDefContext::funcFParam(size_t i) {
  return getRuleContext<sysy2022Parser::FuncFParamContext>(i);
}


size_t sysy2022Parser::FuncDefContext::getRuleIndex() const {
  return sysy2022Parser::RuleFuncDef;
}


std::any sysy2022Parser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::FuncDefContext* sysy2022Parser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 16, sysy2022Parser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    antlrcpp::downCast<FuncDefContext *>(_localctx)->funcType = _input->LT(1);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2060) != 0))) {
      antlrcpp::downCast<FuncDefContext *>(_localctx)->funcType = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(128);
    match(sysy2022Parser::ID);
    setState(129);
    match(sysy2022Parser::T__11);
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2) {
      setState(130);
      funcFParam();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == sysy2022Parser::T__3) {
        setState(131);
        match(sysy2022Parser::T__3);
        setState(132);
        funcFParam();
        setState(137);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(140);
    match(sysy2022Parser::T__12);
    setState(141);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

sysy2022Parser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::FuncFParamContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::FuncFParamContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::FuncFParamContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}


size_t sysy2022Parser::FuncFParamContext::getRuleIndex() const {
  return sysy2022Parser::RuleFuncFParam;
}


std::any sysy2022Parser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::FuncFParamContext* sysy2022Parser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 18, sysy2022Parser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    antlrcpp::downCast<FuncFParamContext *>(_localctx)->basicType = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
      antlrcpp::downCast<FuncFParamContext *>(_localctx)->basicType = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(144);
    match(sysy2022Parser::ID);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__5) {
      setState(145);
      match(sysy2022Parser::T__5);
      setState(146);
      match(sysy2022Parser::T__6);
      setState(157);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == sysy2022Parser::T__5) {
        setState(147);
        match(sysy2022Parser::T__5);
        setState(151);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317808640) != 0)) {
          setState(148);
          expr(0);
          setState(153);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(154);
        match(sysy2022Parser::T__6);
        setState(159);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

sysy2022Parser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::DeclContext *> sysy2022Parser::BlockContext::decl() {
  return getRuleContexts<sysy2022Parser::DeclContext>();
}

sysy2022Parser::DeclContext* sysy2022Parser::BlockContext::decl(size_t i) {
  return getRuleContext<sysy2022Parser::DeclContext>(i);
}

std::vector<sysy2022Parser::StmtContext *> sysy2022Parser::BlockContext::stmt() {
  return getRuleContexts<sysy2022Parser::StmtContext>();
}

sysy2022Parser::StmtContext* sysy2022Parser::BlockContext::stmt(size_t i) {
  return getRuleContext<sysy2022Parser::StmtContext>(i);
}


size_t sysy2022Parser::BlockContext::getRuleIndex() const {
  return sysy2022Parser::RuleBlock;
}


std::any sysy2022Parser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::BlockContext* sysy2022Parser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 20, sysy2022Parser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(sysy2022Parser::T__8);
    setState(167);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120318808622) != 0)) {
      setState(165);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case sysy2022Parser::T__0:
        case sysy2022Parser::T__1:
        case sysy2022Parser::T__2: {
          setState(163);
          decl();
          break;
        }

        case sysy2022Parser::T__4:
        case sysy2022Parser::T__8:
        case sysy2022Parser::T__11:
        case sysy2022Parser::T__13:
        case sysy2022Parser::T__15:
        case sysy2022Parser::T__16:
        case sysy2022Parser::T__17:
        case sysy2022Parser::T__18:
        case sysy2022Parser::T__22:
        case sysy2022Parser::T__23:
        case sysy2022Parser::T__24:
        case sysy2022Parser::ID:
        case sysy2022Parser::INT:
        case sysy2022Parser::FLOAT: {
          setState(164);
          stmt();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(169);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(170);
    match(sysy2022Parser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

sysy2022Parser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::StmtContext::getRuleIndex() const {
  return sysy2022Parser::RuleStmt;
}

void sysy2022Parser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExprStmtContext ------------------------------------------------------------------

sysy2022Parser::ExprContext* sysy2022Parser::ExprStmtContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::ExprStmtContext::ExprStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::ExprStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitExprStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStmtContext ------------------------------------------------------------------

sysy2022Parser::CondContext* sysy2022Parser::WhileStmtContext::cond() {
  return getRuleContext<sysy2022Parser::CondContext>(0);
}

sysy2022Parser::StmtContext* sysy2022Parser::WhileStmtContext::stmt() {
  return getRuleContext<sysy2022Parser::StmtContext>(0);
}

sysy2022Parser::WhileStmtContext::WhileStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

sysy2022Parser::CondContext* sysy2022Parser::IfStmtContext::cond() {
  return getRuleContext<sysy2022Parser::CondContext>(0);
}

std::vector<sysy2022Parser::StmtContext *> sysy2022Parser::IfStmtContext::stmt() {
  return getRuleContexts<sysy2022Parser::StmtContext>();
}

sysy2022Parser::StmtContext* sysy2022Parser::IfStmtContext::stmt(size_t i) {
  return getRuleContext<sysy2022Parser::StmtContext>(i);
}

sysy2022Parser::IfStmtContext::IfStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

sysy2022Parser::BlockContext* sysy2022Parser::BlockStmtContext::block() {
  return getRuleContext<sysy2022Parser::BlockContext>(0);
}

sysy2022Parser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

sysy2022Parser::LValContext* sysy2022Parser::AssignStmtContext::lVal() {
  return getRuleContext<sysy2022Parser::LValContext>(0);
}

sysy2022Parser::ExprContext* sysy2022Parser::AssignStmtContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

sysy2022Parser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

sysy2022Parser::ExprContext* sysy2022Parser::ReturnStmtContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStmtContext ------------------------------------------------------------------

sysy2022Parser::ContinueStmtContext::ContinueStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
sysy2022Parser::StmtContext* sysy2022Parser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 22, sysy2022Parser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<sysy2022Parser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(172);
      lVal();
      setState(173);
      match(sysy2022Parser::T__7);
      setState(174);
      expr(0);
      setState(175);
      match(sysy2022Parser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<sysy2022Parser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(178);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317808640) != 0)) {
        setState(177);
        expr(0);
      }
      setState(180);
      match(sysy2022Parser::T__4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<sysy2022Parser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(181);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<sysy2022Parser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(182);
      match(sysy2022Parser::T__13);
      setState(183);
      match(sysy2022Parser::T__11);
      setState(184);
      cond(0);
      setState(185);
      match(sysy2022Parser::T__12);
      setState(186);
      stmt();
      setState(189);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(187);
        match(sysy2022Parser::T__14);
        setState(188);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<sysy2022Parser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(191);
      match(sysy2022Parser::T__15);
      setState(192);
      match(sysy2022Parser::T__11);
      setState(193);
      cond(0);
      setState(194);
      match(sysy2022Parser::T__12);
      setState(195);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<sysy2022Parser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(197);
      match(sysy2022Parser::T__16);
      setState(198);
      match(sysy2022Parser::T__4);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<sysy2022Parser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(199);
      match(sysy2022Parser::T__17);
      setState(200);
      match(sysy2022Parser::T__4);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<sysy2022Parser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(201);
      match(sysy2022Parser::T__18);
      setState(203);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317808640) != 0)) {
        setState(202);
        expr(0);
      }
      setState(205);
      match(sysy2022Parser::T__4);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

sysy2022Parser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::ExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleExpr;
}

void sysy2022Parser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddSubExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::AddSubExprContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::AddSubExprContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}

sysy2022Parser::AddSubExprContext::AddSubExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::AddSubExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitAddSubExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivModExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::MulDivModExprContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::MulDivModExprContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}

sysy2022Parser::MulDivModExprContext::MulDivModExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::MulDivModExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitMulDivModExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubUnaryExprContext ------------------------------------------------------------------

sysy2022Parser::UnaryExprContext* sysy2022Parser::SubUnaryExprContext::unaryExpr() {
  return getRuleContext<sysy2022Parser::UnaryExprContext>(0);
}

sysy2022Parser::SubUnaryExprContext::SubUnaryExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::SubUnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitSubUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::ExprContext* sysy2022Parser::expr() {
   return expr(0);
}

sysy2022Parser::ExprContext* sysy2022Parser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  sysy2022Parser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  sysy2022Parser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, sysy2022Parser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<SubUnaryExprContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(209);
    unaryExpr();
    _ctx->stop = _input->LT(-1);
    setState(219);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(217);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivModExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(211);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(212);
          antlrcpp::downCast<MulDivModExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
            antlrcpp::downCast<MulDivModExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(213);
          expr(3);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(214);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(215);
          antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == sysy2022Parser::T__22

          || _la == sysy2022Parser::T__23)) {
            antlrcpp::downCast<AddSubExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(216);
          expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(221);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryExprContext ------------------------------------------------------------------

sysy2022Parser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::UnaryExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleUnaryExpr;
}

void sysy2022Parser::UnaryExprContext::copyFrom(UnaryExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RecUnaryExprContext ------------------------------------------------------------------

sysy2022Parser::UnaryExprContext* sysy2022Parser::RecUnaryExprContext::unaryExpr() {
  return getRuleContext<sysy2022Parser::UnaryExprContext>(0);
}

sysy2022Parser::RecUnaryExprContext::RecUnaryExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::RecUnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitRecUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntLiteralContext ------------------------------------------------------------------

tree::TerminalNode* sysy2022Parser::IntLiteralContext::INT() {
  return getToken(sysy2022Parser::INT, 0);
}

sysy2022Parser::IntLiteralContext::IntLiteralContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::IntLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitIntLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatLiteralContext ------------------------------------------------------------------

tree::TerminalNode* sysy2022Parser::FloatLiteralContext::FLOAT() {
  return getToken(sysy2022Parser::FLOAT, 0);
}

sysy2022Parser::FloatLiteralContext::FloatLiteralContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::FloatLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFloatLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LValExprContext ------------------------------------------------------------------

sysy2022Parser::LValContext* sysy2022Parser::LValExprContext::lVal() {
  return getRuleContext<sysy2022Parser::LValContext>(0);
}

sysy2022Parser::LValExprContext::LValExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::LValExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitLValExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallContext ------------------------------------------------------------------

tree::TerminalNode* sysy2022Parser::FuncCallContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::FuncCallContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::FuncCallContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}

sysy2022Parser::FuncCallContext::FuncCallContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExprContext ------------------------------------------------------------------

sysy2022Parser::ExprContext* sysy2022Parser::ParenExprContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::ParenExprContext::ParenExprContext(UnaryExprContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::ParenExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitParenExpr(this);
  else
    return visitor->visitChildren(this);
}
sysy2022Parser::UnaryExprContext* sysy2022Parser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 26, sysy2022Parser::RuleUnaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(244);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<sysy2022Parser::ParenExprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(222);
      match(sysy2022Parser::T__11);
      setState(223);
      expr(0);
      setState(224);
      match(sysy2022Parser::T__12);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<sysy2022Parser::LValExprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(226);
      lVal();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<sysy2022Parser::IntLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(227);
      match(sysy2022Parser::INT);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<sysy2022Parser::FloatLiteralContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(228);
      match(sysy2022Parser::FLOAT);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<sysy2022Parser::FuncCallContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(229);
      match(sysy2022Parser::ID);
      setState(230);
      match(sysy2022Parser::T__11);
      setState(239);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317808640) != 0)) {
        setState(231);
        expr(0);
        setState(236);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == sysy2022Parser::T__3) {
          setState(232);
          match(sysy2022Parser::T__3);
          setState(233);
          expr(0);
          setState(238);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(241);
      match(sysy2022Parser::T__12);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<sysy2022Parser::RecUnaryExprContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(242);
      antlrcpp::downCast<RecUnaryExprContext *>(_localctx)->op = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 58720256) != 0))) {
        antlrcpp::downCast<RecUnaryExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(243);
      unaryExpr();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

sysy2022Parser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::LValContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::LValContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::LValContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}


size_t sysy2022Parser::LValContext::getRuleIndex() const {
  return sysy2022Parser::RuleLVal;
}


std::any sysy2022Parser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::LValContext* sysy2022Parser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 28, sysy2022Parser::RuleLVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(246);
    match(sysy2022Parser::ID);
    setState(253);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(247);
        match(sysy2022Parser::T__5);
        setState(248);
        expr(0);
        setState(249);
        match(sysy2022Parser::T__6); 
      }
      setState(255);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

sysy2022Parser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::CondContext::getRuleIndex() const {
  return sysy2022Parser::RuleCond;
}

void sysy2022Parser::CondContext::copyFrom(CondContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EqExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::CondContext *> sysy2022Parser::EqExprContext::cond() {
  return getRuleContexts<sysy2022Parser::CondContext>();
}

sysy2022Parser::CondContext* sysy2022Parser::EqExprContext::cond(size_t i) {
  return getRuleContext<sysy2022Parser::CondContext>(i);
}

sysy2022Parser::EqExprContext::EqExprContext(CondContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::EqExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitEqExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryExprContext ------------------------------------------------------------------

sysy2022Parser::ExprContext* sysy2022Parser::BinaryExprContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::BinaryExprContext::BinaryExprContext(CondContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::BinaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBinaryExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::CondContext *> sysy2022Parser::OrExprContext::cond() {
  return getRuleContexts<sysy2022Parser::CondContext>();
}

sysy2022Parser::CondContext* sysy2022Parser::OrExprContext::cond(size_t i) {
  return getRuleContext<sysy2022Parser::CondContext>(i);
}

sysy2022Parser::OrExprContext::OrExprContext(CondContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::OrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::CondContext *> sysy2022Parser::RelExprContext::cond() {
  return getRuleContexts<sysy2022Parser::CondContext>();
}

sysy2022Parser::CondContext* sysy2022Parser::RelExprContext::cond(size_t i) {
  return getRuleContext<sysy2022Parser::CondContext>(i);
}

sysy2022Parser::RelExprContext::RelExprContext(CondContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::RelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitRelExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndExprContext ------------------------------------------------------------------

std::vector<sysy2022Parser::CondContext *> sysy2022Parser::AndExprContext::cond() {
  return getRuleContexts<sysy2022Parser::CondContext>();
}

sysy2022Parser::CondContext* sysy2022Parser::AndExprContext::cond(size_t i) {
  return getRuleContext<sysy2022Parser::CondContext>(i);
}

sysy2022Parser::AndExprContext::AndExprContext(CondContext *ctx) { copyFrom(ctx); }


std::any sysy2022Parser::AndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitAndExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::CondContext* sysy2022Parser::cond() {
   return cond(0);
}

sysy2022Parser::CondContext* sysy2022Parser::cond(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  sysy2022Parser::CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, parentState);
  sysy2022Parser::CondContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 30;
  enterRecursionRule(_localctx, 30, sysy2022Parser::RuleCond, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<BinaryExprContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(257);
    expr(0);
    _ctx->stop = _input->LT(-1);
    setState(273);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(271);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<RelExprContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(259);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(260);
          antlrcpp::downCast<RelExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1006632960) != 0))) {
            antlrcpp::downCast<RelExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(261);
          cond(5);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<EqExprContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(262);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(263);
          antlrcpp::downCast<EqExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == sysy2022Parser::T__29

          || _la == sysy2022Parser::T__30)) {
            antlrcpp::downCast<EqExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(264);
          cond(4);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<AndExprContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(265);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(266);
          antlrcpp::downCast<AndExprContext *>(_localctx)->op = match(sysy2022Parser::T__31);
          setState(267);
          cond(3);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<OrExprContext>(_tracker.createInstance<CondContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleCond);
          setState(268);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(269);
          antlrcpp::downCast<OrExprContext *>(_localctx)->op = match(sysy2022Parser::T__32);
          setState(270);
          cond(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(275);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConstExprContext ------------------------------------------------------------------

sysy2022Parser::ConstExprContext::ConstExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::ExprContext* sysy2022Parser::ConstExprContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}


size_t sysy2022Parser::ConstExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleConstExpr;
}


std::any sysy2022Parser::ConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitConstExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::ConstExprContext* sysy2022Parser::constExpr() {
  ConstExprContext *_localctx = _tracker.createInstance<ConstExprContext>(_ctx, getState());
  enterRule(_localctx, 32, sysy2022Parser::RuleConstExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool sysy2022Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 12: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 15: return condSempred(antlrcpp::downCast<CondContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool sysy2022Parser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool sysy2022Parser::condSempred(CondContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void sysy2022Parser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sysy2022ParserInitialize();
#else
  ::antlr4::internal::call_once(sysy2022ParserOnceFlag, sysy2022ParserInitialize);
#endif
}
