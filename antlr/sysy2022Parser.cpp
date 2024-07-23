
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
      "compUnit", "decl", "basicType", "constDecl", "constDef", "constInitVal", 
      "varDecl", "varDef", "initVal", "funcDef", "funcType", "funcFParams", 
      "funcFParam", "block", "blockItem", "stmt", "expr", "unaryExpr", "unaryOp", 
      "funcRParams", "primaryExpr", "lVal", "number", "cond", "constExpr"
    },
    std::vector<std::string>{
      "", "'int'", "'float'", "'const'", "','", "';'", "'['", "']'", "'='", 
      "'{'", "'}'", "'('", "')'", "'void'", "'if'", "'else'", "'while'", 
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
  	4,1,39,311,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,1,0,1,0,5,0,53,8,0,10,0,12,0,56,9,0,
  	1,0,1,0,1,1,1,1,3,1,62,8,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,71,8,3,10,
  	3,12,3,74,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,83,8,4,10,4,12,4,86,9,4,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,96,8,5,10,5,12,5,99,9,5,3,5,101,8,
  	5,1,5,3,5,104,8,5,1,6,1,6,1,6,1,6,5,6,110,8,6,10,6,12,6,113,9,6,1,6,1,
  	6,1,7,1,7,1,7,1,7,1,7,5,7,122,8,7,10,7,12,7,125,9,7,1,7,1,7,3,7,129,8,
  	7,1,8,1,8,1,8,1,8,1,8,5,8,136,8,8,10,8,12,8,139,9,8,3,8,141,8,8,1,8,3,
  	8,144,8,8,1,9,1,9,1,9,1,9,3,9,150,8,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,
  	1,11,5,11,160,8,11,10,11,12,11,163,9,11,1,12,1,12,1,12,1,12,1,12,1,12,
  	5,12,171,8,12,10,12,12,12,174,9,12,1,12,5,12,177,8,12,10,12,12,12,180,
  	9,12,3,12,182,8,12,1,13,1,13,5,13,186,8,13,10,13,12,13,189,9,13,1,13,
  	1,13,1,14,1,14,3,14,195,8,14,1,15,1,15,1,15,1,15,1,15,1,15,3,15,203,8,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,214,8,15,1,15,1,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,228,8,15,1,
  	15,3,15,231,8,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,5,16,242,
  	8,16,10,16,12,16,245,9,16,1,17,1,17,1,17,1,17,3,17,251,8,17,1,17,1,17,
  	1,17,1,17,3,17,257,8,17,1,18,1,18,1,19,1,19,1,19,5,19,264,8,19,10,19,
  	12,19,267,9,19,1,20,1,20,1,20,1,20,1,20,1,20,3,20,275,8,20,1,21,1,21,
  	1,21,1,21,1,21,5,21,282,8,21,10,21,12,21,285,9,21,1,22,1,22,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,5,23,
  	304,8,23,10,23,12,23,307,9,23,1,24,1,24,1,24,0,2,32,46,25,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,0,8,1,0,1,2,
  	2,0,1,2,13,13,1,0,20,22,1,0,23,24,1,0,23,25,1,0,35,36,1,0,26,29,1,0,30,
  	31,329,0,54,1,0,0,0,2,61,1,0,0,0,4,63,1,0,0,0,6,65,1,0,0,0,8,77,1,0,0,
  	0,10,103,1,0,0,0,12,105,1,0,0,0,14,116,1,0,0,0,16,143,1,0,0,0,18,145,
  	1,0,0,0,20,154,1,0,0,0,22,156,1,0,0,0,24,164,1,0,0,0,26,183,1,0,0,0,28,
  	194,1,0,0,0,30,230,1,0,0,0,32,232,1,0,0,0,34,256,1,0,0,0,36,258,1,0,0,
  	0,38,260,1,0,0,0,40,274,1,0,0,0,42,276,1,0,0,0,44,286,1,0,0,0,46,288,
  	1,0,0,0,48,308,1,0,0,0,50,53,3,2,1,0,51,53,3,18,9,0,52,50,1,0,0,0,52,
  	51,1,0,0,0,53,56,1,0,0,0,54,52,1,0,0,0,54,55,1,0,0,0,55,57,1,0,0,0,56,
  	54,1,0,0,0,57,58,5,0,0,1,58,1,1,0,0,0,59,62,3,6,3,0,60,62,3,12,6,0,61,
  	59,1,0,0,0,61,60,1,0,0,0,62,3,1,0,0,0,63,64,7,0,0,0,64,5,1,0,0,0,65,66,
  	5,3,0,0,66,67,3,4,2,0,67,72,3,8,4,0,68,69,5,4,0,0,69,71,3,8,4,0,70,68,
  	1,0,0,0,71,74,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,75,1,0,0,0,74,72,
  	1,0,0,0,75,76,5,5,0,0,76,7,1,0,0,0,77,84,5,34,0,0,78,79,5,6,0,0,79,80,
  	3,48,24,0,80,81,5,7,0,0,81,83,1,0,0,0,82,78,1,0,0,0,83,86,1,0,0,0,84,
  	82,1,0,0,0,84,85,1,0,0,0,85,87,1,0,0,0,86,84,1,0,0,0,87,88,5,8,0,0,88,
  	89,3,10,5,0,89,9,1,0,0,0,90,104,3,48,24,0,91,100,5,9,0,0,92,97,3,10,5,
  	0,93,94,5,4,0,0,94,96,3,10,5,0,95,93,1,0,0,0,96,99,1,0,0,0,97,95,1,0,
  	0,0,97,98,1,0,0,0,98,101,1,0,0,0,99,97,1,0,0,0,100,92,1,0,0,0,100,101,
  	1,0,0,0,101,102,1,0,0,0,102,104,5,10,0,0,103,90,1,0,0,0,103,91,1,0,0,
  	0,104,11,1,0,0,0,105,106,3,4,2,0,106,111,3,14,7,0,107,108,5,4,0,0,108,
  	110,3,14,7,0,109,107,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,
  	1,0,0,0,112,114,1,0,0,0,113,111,1,0,0,0,114,115,5,5,0,0,115,13,1,0,0,
  	0,116,123,5,34,0,0,117,118,5,6,0,0,118,119,3,48,24,0,119,120,5,7,0,0,
  	120,122,1,0,0,0,121,117,1,0,0,0,122,125,1,0,0,0,123,121,1,0,0,0,123,124,
  	1,0,0,0,124,128,1,0,0,0,125,123,1,0,0,0,126,127,5,8,0,0,127,129,3,16,
  	8,0,128,126,1,0,0,0,128,129,1,0,0,0,129,15,1,0,0,0,130,144,3,32,16,0,
  	131,140,5,9,0,0,132,137,3,16,8,0,133,134,5,4,0,0,134,136,3,16,8,0,135,
  	133,1,0,0,0,136,139,1,0,0,0,137,135,1,0,0,0,137,138,1,0,0,0,138,141,1,
  	0,0,0,139,137,1,0,0,0,140,132,1,0,0,0,140,141,1,0,0,0,141,142,1,0,0,0,
  	142,144,5,10,0,0,143,130,1,0,0,0,143,131,1,0,0,0,144,17,1,0,0,0,145,146,
  	3,20,10,0,146,147,5,34,0,0,147,149,5,11,0,0,148,150,3,22,11,0,149,148,
  	1,0,0,0,149,150,1,0,0,0,150,151,1,0,0,0,151,152,5,12,0,0,152,153,3,26,
  	13,0,153,19,1,0,0,0,154,155,7,1,0,0,155,21,1,0,0,0,156,161,3,24,12,0,
  	157,158,5,4,0,0,158,160,3,24,12,0,159,157,1,0,0,0,160,163,1,0,0,0,161,
  	159,1,0,0,0,161,162,1,0,0,0,162,23,1,0,0,0,163,161,1,0,0,0,164,165,3,
  	4,2,0,165,181,5,34,0,0,166,167,5,6,0,0,167,178,5,7,0,0,168,172,5,6,0,
  	0,169,171,3,32,16,0,170,169,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,172,
  	173,1,0,0,0,173,175,1,0,0,0,174,172,1,0,0,0,175,177,5,7,0,0,176,168,1,
  	0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,179,1,0,0,0,179,182,1,0,0,0,
  	180,178,1,0,0,0,181,166,1,0,0,0,181,182,1,0,0,0,182,25,1,0,0,0,183,187,
  	5,9,0,0,184,186,3,28,14,0,185,184,1,0,0,0,186,189,1,0,0,0,187,185,1,0,
  	0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,187,1,0,0,0,190,191,5,10,0,0,
  	191,27,1,0,0,0,192,195,3,2,1,0,193,195,3,30,15,0,194,192,1,0,0,0,194,
  	193,1,0,0,0,195,29,1,0,0,0,196,197,3,42,21,0,197,198,5,8,0,0,198,199,
  	3,32,16,0,199,200,5,5,0,0,200,231,1,0,0,0,201,203,3,32,16,0,202,201,1,
  	0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,231,5,5,0,0,205,231,3,26,13,
  	0,206,207,5,14,0,0,207,208,5,11,0,0,208,209,3,46,23,0,209,210,5,12,0,
  	0,210,213,3,30,15,0,211,212,5,15,0,0,212,214,3,30,15,0,213,211,1,0,0,
  	0,213,214,1,0,0,0,214,231,1,0,0,0,215,216,5,16,0,0,216,217,5,11,0,0,217,
  	218,3,46,23,0,218,219,5,12,0,0,219,220,3,30,15,0,220,231,1,0,0,0,221,
  	222,5,17,0,0,222,231,5,5,0,0,223,224,5,18,0,0,224,231,5,5,0,0,225,227,
  	5,19,0,0,226,228,3,32,16,0,227,226,1,0,0,0,227,228,1,0,0,0,228,229,1,
  	0,0,0,229,231,5,5,0,0,230,196,1,0,0,0,230,202,1,0,0,0,230,205,1,0,0,0,
  	230,206,1,0,0,0,230,215,1,0,0,0,230,221,1,0,0,0,230,223,1,0,0,0,230,225,
  	1,0,0,0,231,31,1,0,0,0,232,233,6,16,-1,0,233,234,3,34,17,0,234,243,1,
  	0,0,0,235,236,10,3,0,0,236,237,7,2,0,0,237,242,3,32,16,4,238,239,10,2,
  	0,0,239,240,7,3,0,0,240,242,3,32,16,3,241,235,1,0,0,0,241,238,1,0,0,0,
  	242,245,1,0,0,0,243,241,1,0,0,0,243,244,1,0,0,0,244,33,1,0,0,0,245,243,
  	1,0,0,0,246,257,3,40,20,0,247,248,5,34,0,0,248,250,5,11,0,0,249,251,3,
  	38,19,0,250,249,1,0,0,0,250,251,1,0,0,0,251,252,1,0,0,0,252,257,5,12,
  	0,0,253,254,3,36,18,0,254,255,3,34,17,0,255,257,1,0,0,0,256,246,1,0,0,
  	0,256,247,1,0,0,0,256,253,1,0,0,0,257,35,1,0,0,0,258,259,7,4,0,0,259,
  	37,1,0,0,0,260,265,3,32,16,0,261,262,5,4,0,0,262,264,3,32,16,0,263,261,
  	1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,1,0,0,0,266,39,1,0,0,
  	0,267,265,1,0,0,0,268,269,5,11,0,0,269,270,3,32,16,0,270,271,5,12,0,0,
  	271,275,1,0,0,0,272,275,3,42,21,0,273,275,3,44,22,0,274,268,1,0,0,0,274,
  	272,1,0,0,0,274,273,1,0,0,0,275,41,1,0,0,0,276,283,5,34,0,0,277,278,5,
  	6,0,0,278,279,3,32,16,0,279,280,5,7,0,0,280,282,1,0,0,0,281,277,1,0,0,
  	0,282,285,1,0,0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,43,1,0,0,0,285,
  	283,1,0,0,0,286,287,7,5,0,0,287,45,1,0,0,0,288,289,6,23,-1,0,289,290,
  	3,32,16,0,290,305,1,0,0,0,291,292,10,5,0,0,292,293,7,6,0,0,293,304,3,
  	46,23,6,294,295,10,4,0,0,295,296,7,7,0,0,296,304,3,46,23,5,297,298,10,
  	3,0,0,298,299,5,32,0,0,299,304,3,46,23,4,300,301,10,2,0,0,301,302,5,33,
  	0,0,302,304,3,46,23,3,303,291,1,0,0,0,303,294,1,0,0,0,303,297,1,0,0,0,
  	303,300,1,0,0,0,304,307,1,0,0,0,305,303,1,0,0,0,305,306,1,0,0,0,306,47,
  	1,0,0,0,307,305,1,0,0,0,308,309,3,32,16,0,309,49,1,0,0,0,34,52,54,61,
  	72,84,97,100,103,111,123,128,137,140,143,149,161,172,178,181,187,194,
  	202,213,227,230,241,243,250,256,265,274,283,303,305
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
    setState(54);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8206) != 0)) {
      setState(52);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(50);
        decl();
        break;
      }

      case 2: {
        setState(51);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(56);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(57);
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
    setState(61);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(59);
        constDecl();
        break;
      }

      case sysy2022Parser::T__0:
      case sysy2022Parser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(60);
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

//----------------- BasicTypeContext ------------------------------------------------------------------

sysy2022Parser::BasicTypeContext::BasicTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::BasicTypeContext::getRuleIndex() const {
  return sysy2022Parser::RuleBasicType;
}


std::any sysy2022Parser::BasicTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBasicType(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::BasicTypeContext* sysy2022Parser::basicType() {
  BasicTypeContext *_localctx = _tracker.createInstance<BasicTypeContext>(_ctx, getState());
  enterRule(_localctx, 4, sysy2022Parser::RuleBasicType);
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
    setState(63);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__0

    || _la == sysy2022Parser::T__1)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
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

sysy2022Parser::BasicTypeContext* sysy2022Parser::ConstDeclContext::basicType() {
  return getRuleContext<sysy2022Parser::BasicTypeContext>(0);
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
  enterRule(_localctx, 6, sysy2022Parser::RuleConstDecl);
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
    setState(65);
    match(sysy2022Parser::T__2);
    setState(66);
    basicType();
    setState(67);
    constDef();
    setState(72);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(68);
      match(sysy2022Parser::T__3);
      setState(69);
      constDef();
      setState(74);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(75);
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
  enterRule(_localctx, 8, sysy2022Parser::RuleConstDef);
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
    setState(77);
    match(sysy2022Parser::ID);
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(78);
      match(sysy2022Parser::T__5);
      setState(79);
      constExpr();
      setState(80);
      match(sysy2022Parser::T__6);
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(87);
    match(sysy2022Parser::T__7);
    setState(88);
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
  enterRule(_localctx, 10, sysy2022Parser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10:
      case sysy2022Parser::T__22:
      case sysy2022Parser::T__23:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(90);
        constExpr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(91);
        match(sysy2022Parser::T__8);
        setState(100);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317807104) != 0)) {
          setState(92);
          constInitVal();
          setState(97);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(93);
            match(sysy2022Parser::T__3);
            setState(94);
            constInitVal();
            setState(99);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(102);
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

sysy2022Parser::BasicTypeContext* sysy2022Parser::VarDeclContext::basicType() {
  return getRuleContext<sysy2022Parser::BasicTypeContext>(0);
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
  enterRule(_localctx, 12, sysy2022Parser::RuleVarDecl);
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
    setState(105);
    basicType();
    setState(106);
    varDef();
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(107);
      match(sysy2022Parser::T__3);
      setState(108);
      varDef();
      setState(113);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(114);
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
  enterRule(_localctx, 14, sysy2022Parser::RuleVarDef);
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
    setState(116);
    match(sysy2022Parser::ID);
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(117);
      match(sysy2022Parser::T__5);
      setState(118);
      constExpr();
      setState(119);
      match(sysy2022Parser::T__6);
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(128);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__7) {
      setState(126);
      match(sysy2022Parser::T__7);
      setState(127);
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
  enterRule(_localctx, 16, sysy2022Parser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(143);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10:
      case sysy2022Parser::T__22:
      case sysy2022Parser::T__23:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(130);
        expr(0);
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(131);
        match(sysy2022Parser::T__8);
        setState(140);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317807104) != 0)) {
          setState(132);
          initVal();
          setState(137);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(133);
            match(sysy2022Parser::T__3);
            setState(134);
            initVal();
            setState(139);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(142);
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

sysy2022Parser::FuncTypeContext* sysy2022Parser::FuncDefContext::funcType() {
  return getRuleContext<sysy2022Parser::FuncTypeContext>(0);
}

tree::TerminalNode* sysy2022Parser::FuncDefContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

sysy2022Parser::BlockContext* sysy2022Parser::FuncDefContext::block() {
  return getRuleContext<sysy2022Parser::BlockContext>(0);
}

sysy2022Parser::FuncFParamsContext* sysy2022Parser::FuncDefContext::funcFParams() {
  return getRuleContext<sysy2022Parser::FuncFParamsContext>(0);
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
  enterRule(_localctx, 18, sysy2022Parser::RuleFuncDef);
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
    setState(145);
    funcType();
    setState(146);
    match(sysy2022Parser::ID);
    setState(147);
    match(sysy2022Parser::T__10);
    setState(149);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__0

    || _la == sysy2022Parser::T__1) {
      setState(148);
      funcFParams();
    }
    setState(151);
    match(sysy2022Parser::T__11);
    setState(152);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

sysy2022Parser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::FuncTypeContext::getRuleIndex() const {
  return sysy2022Parser::RuleFuncType;
}


std::any sysy2022Parser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::FuncTypeContext* sysy2022Parser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, sysy2022Parser::RuleFuncType);
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
    setState(154);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8198) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

sysy2022Parser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::FuncFParamContext *> sysy2022Parser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<sysy2022Parser::FuncFParamContext>();
}

sysy2022Parser::FuncFParamContext* sysy2022Parser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<sysy2022Parser::FuncFParamContext>(i);
}


size_t sysy2022Parser::FuncFParamsContext::getRuleIndex() const {
  return sysy2022Parser::RuleFuncFParams;
}


std::any sysy2022Parser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::FuncFParamsContext* sysy2022Parser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 22, sysy2022Parser::RuleFuncFParams);
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
    setState(156);
    funcFParam();
    setState(161);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(157);
      match(sysy2022Parser::T__3);
      setState(158);
      funcFParam();
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
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

sysy2022Parser::BasicTypeContext* sysy2022Parser::FuncFParamContext::basicType() {
  return getRuleContext<sysy2022Parser::BasicTypeContext>(0);
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
  enterRule(_localctx, 24, sysy2022Parser::RuleFuncFParam);
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
    setState(164);
    basicType();
    setState(165);
    match(sysy2022Parser::ID);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__5) {
      setState(166);
      match(sysy2022Parser::T__5);
      setState(167);
      match(sysy2022Parser::T__6);
      setState(178);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == sysy2022Parser::T__5) {
        setState(168);
        match(sysy2022Parser::T__5);
        setState(172);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120317806592) != 0)) {
          setState(169);
          expr(0);
          setState(174);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(175);
        match(sysy2022Parser::T__6);
        setState(180);
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

std::vector<sysy2022Parser::BlockItemContext *> sysy2022Parser::BlockContext::blockItem() {
  return getRuleContexts<sysy2022Parser::BlockItemContext>();
}

sysy2022Parser::BlockItemContext* sysy2022Parser::BlockContext::blockItem(size_t i) {
  return getRuleContext<sysy2022Parser::BlockItemContext>(i);
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
  enterRule(_localctx, 26, sysy2022Parser::RuleBlock);
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
    setState(183);
    match(sysy2022Parser::T__8);
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120318806574) != 0)) {
      setState(184);
      blockItem();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    match(sysy2022Parser::T__9);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

sysy2022Parser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::DeclContext* sysy2022Parser::BlockItemContext::decl() {
  return getRuleContext<sysy2022Parser::DeclContext>(0);
}

sysy2022Parser::StmtContext* sysy2022Parser::BlockItemContext::stmt() {
  return getRuleContext<sysy2022Parser::StmtContext>(0);
}


size_t sysy2022Parser::BlockItemContext::getRuleIndex() const {
  return sysy2022Parser::RuleBlockItem;
}


std::any sysy2022Parser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::BlockItemContext* sysy2022Parser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 28, sysy2022Parser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(194);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__0:
      case sysy2022Parser::T__1:
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(192);
        decl();
        break;
      }

      case sysy2022Parser::T__4:
      case sysy2022Parser::T__8:
      case sysy2022Parser::T__10:
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
        enterOuterAlt(_localctx, 2);
        setState(193);
        stmt();
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
  enterRule(_localctx, 30, sysy2022Parser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<sysy2022Parser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(196);
      lVal();
      setState(197);
      match(sysy2022Parser::T__7);
      setState(198);
      expr(0);
      setState(199);
      match(sysy2022Parser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<sysy2022Parser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(202);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317806592) != 0)) {
        setState(201);
        expr(0);
      }
      setState(204);
      match(sysy2022Parser::T__4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<sysy2022Parser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(205);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<sysy2022Parser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(206);
      match(sysy2022Parser::T__13);
      setState(207);
      match(sysy2022Parser::T__10);
      setState(208);
      cond(0);
      setState(209);
      match(sysy2022Parser::T__11);
      setState(210);
      stmt();
      setState(213);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(211);
        match(sysy2022Parser::T__14);
        setState(212);
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
      setState(215);
      match(sysy2022Parser::T__15);
      setState(216);
      match(sysy2022Parser::T__10);
      setState(217);
      cond(0);
      setState(218);
      match(sysy2022Parser::T__11);
      setState(219);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<sysy2022Parser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(221);
      match(sysy2022Parser::T__16);
      setState(222);
      match(sysy2022Parser::T__4);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<sysy2022Parser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(223);
      match(sysy2022Parser::T__17);
      setState(224);
      match(sysy2022Parser::T__4);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<sysy2022Parser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(225);
      match(sysy2022Parser::T__18);
      setState(227);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317806592) != 0)) {
        setState(226);
        expr(0);
      }
      setState(229);
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

sysy2022Parser::UnaryExprContext* sysy2022Parser::ExprContext::unaryExpr() {
  return getRuleContext<sysy2022Parser::UnaryExprContext>(0);
}

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::ExprContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::ExprContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}


size_t sysy2022Parser::ExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleExpr;
}


std::any sysy2022Parser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitExpr(this);
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
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, sysy2022Parser::RuleExpr, precedence);

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
    setState(233);
    unaryExpr();
    _ctx->stop = _input->LT(-1);
    setState(243);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(241);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(235);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(236);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(237);
          expr(4);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(238);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(239);
          _la = _input->LA(1);
          if (!(_la == sysy2022Parser::T__22

          || _la == sysy2022Parser::T__23)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(240);
          expr(3);
          break;
        }

        default:
          break;
        } 
      }
      setState(245);
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

sysy2022Parser::PrimaryExprContext* sysy2022Parser::UnaryExprContext::primaryExpr() {
  return getRuleContext<sysy2022Parser::PrimaryExprContext>(0);
}

tree::TerminalNode* sysy2022Parser::UnaryExprContext::ID() {
  return getToken(sysy2022Parser::ID, 0);
}

sysy2022Parser::FuncRParamsContext* sysy2022Parser::UnaryExprContext::funcRParams() {
  return getRuleContext<sysy2022Parser::FuncRParamsContext>(0);
}

sysy2022Parser::UnaryOpContext* sysy2022Parser::UnaryExprContext::unaryOp() {
  return getRuleContext<sysy2022Parser::UnaryOpContext>(0);
}

sysy2022Parser::UnaryExprContext* sysy2022Parser::UnaryExprContext::unaryExpr() {
  return getRuleContext<sysy2022Parser::UnaryExprContext>(0);
}


size_t sysy2022Parser::UnaryExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleUnaryExpr;
}


std::any sysy2022Parser::UnaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitUnaryExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::UnaryExprContext* sysy2022Parser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 34, sysy2022Parser::RuleUnaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(256);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(246);
      primaryExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(247);
      match(sysy2022Parser::ID);
      setState(248);
      match(sysy2022Parser::T__10);
      setState(250);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120317806592) != 0)) {
        setState(249);
        funcRParams();
      }
      setState(252);
      match(sysy2022Parser::T__11);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(253);
      unaryOp();
      setState(254);
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

//----------------- UnaryOpContext ------------------------------------------------------------------

sysy2022Parser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t sysy2022Parser::UnaryOpContext::getRuleIndex() const {
  return sysy2022Parser::RuleUnaryOp;
}


std::any sysy2022Parser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::UnaryOpContext* sysy2022Parser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 36, sysy2022Parser::RuleUnaryOp);
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
    setState(258);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 58720256) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

sysy2022Parser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::ExprContext *> sysy2022Parser::FuncRParamsContext::expr() {
  return getRuleContexts<sysy2022Parser::ExprContext>();
}

sysy2022Parser::ExprContext* sysy2022Parser::FuncRParamsContext::expr(size_t i) {
  return getRuleContext<sysy2022Parser::ExprContext>(i);
}


size_t sysy2022Parser::FuncRParamsContext::getRuleIndex() const {
  return sysy2022Parser::RuleFuncRParams;
}


std::any sysy2022Parser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::FuncRParamsContext* sysy2022Parser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 38, sysy2022Parser::RuleFuncRParams);
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
    setState(260);
    expr(0);
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(261);
      match(sysy2022Parser::T__3);
      setState(262);
      expr(0);
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

sysy2022Parser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::ExprContext* sysy2022Parser::PrimaryExprContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::LValContext* sysy2022Parser::PrimaryExprContext::lVal() {
  return getRuleContext<sysy2022Parser::LValContext>(0);
}

sysy2022Parser::NumberContext* sysy2022Parser::PrimaryExprContext::number() {
  return getRuleContext<sysy2022Parser::NumberContext>(0);
}


size_t sysy2022Parser::PrimaryExprContext::getRuleIndex() const {
  return sysy2022Parser::RulePrimaryExpr;
}


std::any sysy2022Parser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::PrimaryExprContext* sysy2022Parser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 40, sysy2022Parser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(268);
        match(sysy2022Parser::T__10);
        setState(269);
        expr(0);
        setState(270);
        match(sysy2022Parser::T__11);
        break;
      }

      case sysy2022Parser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(272);
        lVal();
        break;
      }

      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(273);
        number();
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
  enterRule(_localctx, 42, sysy2022Parser::RuleLVal);

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
    setState(276);
    match(sysy2022Parser::ID);
    setState(283);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(277);
        match(sysy2022Parser::T__5);
        setState(278);
        expr(0);
        setState(279);
        match(sysy2022Parser::T__6); 
      }
      setState(285);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

sysy2022Parser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* sysy2022Parser::NumberContext::INT() {
  return getToken(sysy2022Parser::INT, 0);
}

tree::TerminalNode* sysy2022Parser::NumberContext::FLOAT() {
  return getToken(sysy2022Parser::FLOAT, 0);
}


size_t sysy2022Parser::NumberContext::getRuleIndex() const {
  return sysy2022Parser::RuleNumber;
}


std::any sysy2022Parser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::NumberContext* sysy2022Parser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 44, sysy2022Parser::RuleNumber);
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
    setState(286);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::INT

    || _la == sysy2022Parser::FLOAT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
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

sysy2022Parser::ExprContext* sysy2022Parser::CondContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

std::vector<sysy2022Parser::CondContext *> sysy2022Parser::CondContext::cond() {
  return getRuleContexts<sysy2022Parser::CondContext>();
}

sysy2022Parser::CondContext* sysy2022Parser::CondContext::cond(size_t i) {
  return getRuleContext<sysy2022Parser::CondContext>(i);
}


size_t sysy2022Parser::CondContext::getRuleIndex() const {
  return sysy2022Parser::RuleCond;
}


std::any sysy2022Parser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitCond(this);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, sysy2022Parser::RuleCond, precedence);

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
    setState(289);
    expr(0);
    _ctx->stop = _input->LT(-1);
    setState(305);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(303);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(291);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(292);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 1006632960) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(293);
          cond(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(294);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(295);
          _la = _input->LA(1);
          if (!(_la == sysy2022Parser::T__29

          || _la == sysy2022Parser::T__30)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(296);
          cond(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(297);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(298);
          match(sysy2022Parser::T__31);
          setState(299);
          cond(4);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<CondContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleCond);
          setState(300);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(301);
          match(sysy2022Parser::T__32);
          setState(302);
          cond(3);
          break;
        }

        default:
          break;
        } 
      }
      setState(307);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
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
  enterRule(_localctx, 48, sysy2022Parser::RuleConstExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
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
    case 16: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 23: return condSempred(antlrcpp::downCast<CondContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool sysy2022Parser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool sysy2022Parser::condSempred(CondContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);

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
