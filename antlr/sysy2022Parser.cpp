
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
      "varDef", "initVal", "funcDef", "funcFParams", "funcFParam", "block", 
      "blockItem", "stmt", "expr", "addExpr", "mulExpr", "unaryExpr", "unaryOp", 
      "funcRParams", "primaryExpr", "lVal", "number", "cond", "lOrExpr", 
      "lAndExpr", "eqExpr", "relExpr", "constExpr"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'float'", "','", "';'", "'['", "']'", "'='", 
      "'{'", "'}'", "'void'", "'('", "')'", "'if'", "'else'", "'while'", 
      "'break'", "'continue'", "'return'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'!'", "'||'", "'&&'", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "ID", "INT", "FLOAT", "BlockComment", "LineComment", "Blank"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,331,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,1,0,1,0,5,0,61,8,0,10,0,12,0,64,9,0,1,0,1,0,1,1,1,1,3,1,70,8,1,1,2,
  	1,2,1,2,1,2,1,2,5,2,77,8,2,10,2,12,2,80,9,2,1,2,1,2,1,3,1,3,1,3,1,3,1,
  	3,5,3,89,8,3,10,3,12,3,92,9,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,102,
  	8,4,10,4,12,4,105,9,4,3,4,107,8,4,1,4,3,4,110,8,4,1,5,1,5,1,5,1,5,5,5,
  	116,8,5,10,5,12,5,119,9,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,5,6,128,8,6,10,
  	6,12,6,131,9,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,5,7,141,8,7,10,7,12,7,
  	144,9,7,3,7,146,8,7,1,7,3,7,149,8,7,1,8,1,8,1,8,1,8,3,8,155,8,8,1,8,1,
  	8,1,8,1,9,1,9,1,9,5,9,163,8,9,10,9,12,9,166,9,9,1,10,1,10,1,10,1,10,1,
  	10,1,10,5,10,174,8,10,10,10,12,10,177,9,10,1,10,5,10,180,8,10,10,10,12,
  	10,183,9,10,3,10,185,8,10,1,11,1,11,5,11,189,8,11,10,11,12,11,192,9,11,
  	1,11,1,11,1,12,1,12,3,12,198,8,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,216,8,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,230,8,13,1,13,
  	3,13,233,8,13,1,14,1,14,1,15,1,15,1,15,5,15,240,8,15,10,15,12,15,243,
  	9,15,1,16,1,16,1,16,5,16,248,8,16,10,16,12,16,251,9,16,1,17,1,17,1,17,
  	1,17,3,17,257,8,17,1,17,1,17,1,17,1,17,3,17,263,8,17,1,18,1,18,1,19,1,
  	19,1,19,5,19,270,8,19,10,19,12,19,273,9,19,1,20,1,20,1,20,1,20,1,20,1,
  	20,3,20,281,8,20,1,21,1,21,1,21,1,21,1,21,5,21,288,8,21,10,21,12,21,291,
  	9,21,1,22,1,22,1,23,1,23,1,24,1,24,1,24,5,24,300,8,24,10,24,12,24,303,
  	9,24,1,25,1,25,1,25,5,25,308,8,25,10,25,12,25,311,9,25,1,26,1,26,1,26,
  	5,26,316,8,26,10,26,12,26,319,9,26,1,27,1,27,1,27,5,27,324,8,27,10,27,
  	12,27,327,9,27,1,28,1,28,1,28,0,0,29,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,0,8,1,0,2,3,2,0,2,3,11,
  	11,1,0,20,21,1,0,22,24,2,0,20,21,25,25,1,0,35,36,1,0,28,29,1,0,30,33,
  	343,0,62,1,0,0,0,2,69,1,0,0,0,4,71,1,0,0,0,6,83,1,0,0,0,8,109,1,0,0,0,
  	10,111,1,0,0,0,12,122,1,0,0,0,14,148,1,0,0,0,16,150,1,0,0,0,18,159,1,
  	0,0,0,20,167,1,0,0,0,22,186,1,0,0,0,24,197,1,0,0,0,26,232,1,0,0,0,28,
  	234,1,0,0,0,30,236,1,0,0,0,32,244,1,0,0,0,34,262,1,0,0,0,36,264,1,0,0,
  	0,38,266,1,0,0,0,40,280,1,0,0,0,42,282,1,0,0,0,44,292,1,0,0,0,46,294,
  	1,0,0,0,48,296,1,0,0,0,50,304,1,0,0,0,52,312,1,0,0,0,54,320,1,0,0,0,56,
  	328,1,0,0,0,58,61,3,2,1,0,59,61,3,16,8,0,60,58,1,0,0,0,60,59,1,0,0,0,
  	61,64,1,0,0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,65,1,0,0,0,64,62,1,0,0,0,
  	65,66,5,0,0,1,66,1,1,0,0,0,67,70,3,4,2,0,68,70,3,10,5,0,69,67,1,0,0,0,
  	69,68,1,0,0,0,70,3,1,0,0,0,71,72,5,1,0,0,72,73,7,0,0,0,73,78,3,6,3,0,
  	74,75,5,4,0,0,75,77,3,6,3,0,76,74,1,0,0,0,77,80,1,0,0,0,78,76,1,0,0,0,
  	78,79,1,0,0,0,79,81,1,0,0,0,80,78,1,0,0,0,81,82,5,5,0,0,82,5,1,0,0,0,
  	83,90,5,34,0,0,84,85,5,6,0,0,85,86,3,56,28,0,86,87,5,7,0,0,87,89,1,0,
  	0,0,88,84,1,0,0,0,89,92,1,0,0,0,90,88,1,0,0,0,90,91,1,0,0,0,91,93,1,0,
  	0,0,92,90,1,0,0,0,93,94,5,8,0,0,94,95,3,8,4,0,95,7,1,0,0,0,96,110,3,56,
  	28,0,97,106,5,9,0,0,98,103,3,8,4,0,99,100,5,4,0,0,100,102,3,8,4,0,101,
  	99,1,0,0,0,102,105,1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,107,1,
  	0,0,0,105,103,1,0,0,0,106,98,1,0,0,0,106,107,1,0,0,0,107,108,1,0,0,0,
  	108,110,5,10,0,0,109,96,1,0,0,0,109,97,1,0,0,0,110,9,1,0,0,0,111,112,
  	7,0,0,0,112,117,3,12,6,0,113,114,5,4,0,0,114,116,3,12,6,0,115,113,1,0,
  	0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,120,1,0,0,0,119,
  	117,1,0,0,0,120,121,5,5,0,0,121,11,1,0,0,0,122,129,5,34,0,0,123,124,5,
  	6,0,0,124,125,3,56,28,0,125,126,5,7,0,0,126,128,1,0,0,0,127,123,1,0,0,
  	0,128,131,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,132,1,0,0,0,131,
  	129,1,0,0,0,132,133,5,8,0,0,133,134,3,14,7,0,134,13,1,0,0,0,135,149,3,
  	28,14,0,136,145,5,9,0,0,137,142,3,14,7,0,138,139,5,4,0,0,139,141,3,14,
  	7,0,140,138,1,0,0,0,141,144,1,0,0,0,142,140,1,0,0,0,142,143,1,0,0,0,143,
  	146,1,0,0,0,144,142,1,0,0,0,145,137,1,0,0,0,145,146,1,0,0,0,146,147,1,
  	0,0,0,147,149,5,10,0,0,148,135,1,0,0,0,148,136,1,0,0,0,149,15,1,0,0,0,
  	150,151,7,1,0,0,151,152,5,34,0,0,152,154,5,12,0,0,153,155,3,18,9,0,154,
  	153,1,0,0,0,154,155,1,0,0,0,155,156,1,0,0,0,156,157,5,13,0,0,157,158,
  	3,22,11,0,158,17,1,0,0,0,159,164,3,20,10,0,160,161,5,4,0,0,161,163,3,
  	20,10,0,162,160,1,0,0,0,163,166,1,0,0,0,164,162,1,0,0,0,164,165,1,0,0,
  	0,165,19,1,0,0,0,166,164,1,0,0,0,167,168,7,0,0,0,168,184,5,34,0,0,169,
  	170,5,6,0,0,170,181,5,7,0,0,171,175,5,6,0,0,172,174,3,28,14,0,173,172,
  	1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,178,1,0,0,
  	0,177,175,1,0,0,0,178,180,5,7,0,0,179,171,1,0,0,0,180,183,1,0,0,0,181,
  	179,1,0,0,0,181,182,1,0,0,0,182,185,1,0,0,0,183,181,1,0,0,0,184,169,1,
  	0,0,0,184,185,1,0,0,0,185,21,1,0,0,0,186,190,5,9,0,0,187,189,3,24,12,
  	0,188,187,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,
  	193,1,0,0,0,192,190,1,0,0,0,193,194,5,10,0,0,194,23,1,0,0,0,195,198,3,
  	2,1,0,196,198,3,26,13,0,197,195,1,0,0,0,197,196,1,0,0,0,198,25,1,0,0,
  	0,199,200,3,42,21,0,200,201,5,8,0,0,201,202,3,28,14,0,202,203,5,5,0,0,
  	203,233,1,0,0,0,204,205,3,28,14,0,205,206,5,5,0,0,206,233,1,0,0,0,207,
  	233,3,22,11,0,208,209,5,14,0,0,209,210,5,12,0,0,210,211,3,46,23,0,211,
  	212,5,13,0,0,212,215,3,26,13,0,213,214,5,15,0,0,214,216,3,26,13,0,215,
  	213,1,0,0,0,215,216,1,0,0,0,216,233,1,0,0,0,217,218,5,16,0,0,218,219,
  	5,12,0,0,219,220,3,46,23,0,220,221,5,13,0,0,221,222,3,26,13,0,222,233,
  	1,0,0,0,223,224,5,17,0,0,224,233,5,5,0,0,225,226,5,18,0,0,226,233,5,5,
  	0,0,227,229,5,19,0,0,228,230,3,28,14,0,229,228,1,0,0,0,229,230,1,0,0,
  	0,230,231,1,0,0,0,231,233,5,5,0,0,232,199,1,0,0,0,232,204,1,0,0,0,232,
  	207,1,0,0,0,232,208,1,0,0,0,232,217,1,0,0,0,232,223,1,0,0,0,232,225,1,
  	0,0,0,232,227,1,0,0,0,233,27,1,0,0,0,234,235,3,30,15,0,235,29,1,0,0,0,
  	236,241,3,32,16,0,237,238,7,2,0,0,238,240,3,32,16,0,239,237,1,0,0,0,240,
  	243,1,0,0,0,241,239,1,0,0,0,241,242,1,0,0,0,242,31,1,0,0,0,243,241,1,
  	0,0,0,244,249,3,34,17,0,245,246,7,3,0,0,246,248,3,34,17,0,247,245,1,0,
  	0,0,248,251,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,33,1,0,0,0,251,
  	249,1,0,0,0,252,263,3,40,20,0,253,254,5,34,0,0,254,256,5,12,0,0,255,257,
  	3,38,19,0,256,255,1,0,0,0,256,257,1,0,0,0,257,258,1,0,0,0,258,263,5,13,
  	0,0,259,260,3,36,18,0,260,261,3,34,17,0,261,263,1,0,0,0,262,252,1,0,0,
  	0,262,253,1,0,0,0,262,259,1,0,0,0,263,35,1,0,0,0,264,265,7,4,0,0,265,
  	37,1,0,0,0,266,271,3,28,14,0,267,268,5,4,0,0,268,270,3,28,14,0,269,267,
  	1,0,0,0,270,273,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,39,1,0,0,
  	0,273,271,1,0,0,0,274,275,5,12,0,0,275,276,3,28,14,0,276,277,5,13,0,0,
  	277,281,1,0,0,0,278,281,3,42,21,0,279,281,3,44,22,0,280,274,1,0,0,0,280,
  	278,1,0,0,0,280,279,1,0,0,0,281,41,1,0,0,0,282,289,5,34,0,0,283,284,5,
  	6,0,0,284,285,3,28,14,0,285,286,5,7,0,0,286,288,1,0,0,0,287,283,1,0,0,
  	0,288,291,1,0,0,0,289,287,1,0,0,0,289,290,1,0,0,0,290,43,1,0,0,0,291,
  	289,1,0,0,0,292,293,7,5,0,0,293,45,1,0,0,0,294,295,3,48,24,0,295,47,1,
  	0,0,0,296,301,3,50,25,0,297,298,5,26,0,0,298,300,3,50,25,0,299,297,1,
  	0,0,0,300,303,1,0,0,0,301,299,1,0,0,0,301,302,1,0,0,0,302,49,1,0,0,0,
  	303,301,1,0,0,0,304,309,3,52,26,0,305,306,5,27,0,0,306,308,3,52,26,0,
  	307,305,1,0,0,0,308,311,1,0,0,0,309,307,1,0,0,0,309,310,1,0,0,0,310,51,
  	1,0,0,0,311,309,1,0,0,0,312,317,3,54,27,0,313,314,7,6,0,0,314,316,3,54,
  	27,0,315,313,1,0,0,0,316,319,1,0,0,0,317,315,1,0,0,0,317,318,1,0,0,0,
  	318,53,1,0,0,0,319,317,1,0,0,0,320,325,3,30,15,0,321,322,7,7,0,0,322,
  	324,3,30,15,0,323,321,1,0,0,0,324,327,1,0,0,0,325,323,1,0,0,0,325,326,
  	1,0,0,0,326,55,1,0,0,0,327,325,1,0,0,0,328,329,3,30,15,0,329,57,1,0,0,
  	0,34,60,62,69,78,90,103,106,109,117,129,142,145,148,154,164,175,181,184,
  	190,197,215,229,232,241,249,256,262,271,280,289,301,309,317,325
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
    setState(62);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2062) != 0)) {
      setState(60);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(58);
        decl();
        break;
      }

      case 2: {
        setState(59);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(64);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(65);
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
    enterOuterAlt(_localctx, 1);
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__0: {
        setState(67);
        constDecl();
        break;
      }

      case sysy2022Parser::T__1:
      case sysy2022Parser::T__2: {
        setState(68);
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
    setState(71);
    match(sysy2022Parser::T__0);
    setState(72);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(73);
    constDef();
    setState(78);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(74);
      match(sysy2022Parser::T__3);
      setState(75);
      constDef();
      setState(80);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(81);
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
    setState(83);
    match(sysy2022Parser::ID);
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(84);
      match(sysy2022Parser::T__5);
      setState(85);
      constExpr();
      setState(86);
      match(sysy2022Parser::T__6);
      setState(92);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(93);
    match(sysy2022Parser::T__7);
    setState(94);
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
    setState(109);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__11:
      case sysy2022Parser::T__19:
      case sysy2022Parser::T__20:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(96);
        constExpr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(97);
        match(sysy2022Parser::T__8);
        setState(106);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295789056) != 0)) {
          setState(98);
          constInitVal();
          setState(103);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(99);
            match(sysy2022Parser::T__3);
            setState(100);
            constInitVal();
            setState(105);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(108);
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
    setState(111);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(112);
    varDef();
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(113);
      match(sysy2022Parser::T__3);
      setState(114);
      varDef();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(120);
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

sysy2022Parser::InitValContext* sysy2022Parser::VarDefContext::initVal() {
  return getRuleContext<sysy2022Parser::InitValContext>(0);
}

std::vector<sysy2022Parser::ConstExprContext *> sysy2022Parser::VarDefContext::constExpr() {
  return getRuleContexts<sysy2022Parser::ConstExprContext>();
}

sysy2022Parser::ConstExprContext* sysy2022Parser::VarDefContext::constExpr(size_t i) {
  return getRuleContext<sysy2022Parser::ConstExprContext>(i);
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
    setState(122);
    match(sysy2022Parser::ID);
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(123);
      match(sysy2022Parser::T__5);
      setState(124);
      constExpr();
      setState(125);
      match(sysy2022Parser::T__6);
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(132);
    match(sysy2022Parser::T__7);
    setState(133);
    initVal();
   
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
    setState(148);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__11:
      case sysy2022Parser::T__19:
      case sysy2022Parser::T__20:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(135);
        expr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(136);
        match(sysy2022Parser::T__8);
        setState(145);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295789056) != 0)) {
          setState(137);
          initVal();
          setState(142);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(138);
            match(sysy2022Parser::T__3);
            setState(139);
            initVal();
            setState(144);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(147);
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
    setState(150);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2060) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(151);
    match(sysy2022Parser::ID);
    setState(152);
    match(sysy2022Parser::T__11);
    setState(154);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2) {
      setState(153);
      funcFParams();
    }
    setState(156);
    match(sysy2022Parser::T__12);
    setState(157);
    block();
   
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
  enterRule(_localctx, 18, sysy2022Parser::RuleFuncFParams);
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
    setState(159);
    funcFParam();
    setState(164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(160);
      match(sysy2022Parser::T__3);
      setState(161);
      funcFParam();
      setState(166);
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
  enterRule(_localctx, 20, sysy2022Parser::RuleFuncFParam);
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
    setState(167);
    _la = _input->LA(1);
    if (!(_la == sysy2022Parser::T__1

    || _la == sysy2022Parser::T__2)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(168);
    match(sysy2022Parser::ID);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__5) {
      setState(169);
      match(sysy2022Parser::T__5);
      setState(170);
      match(sysy2022Parser::T__6);
      setState(181);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == sysy2022Parser::T__5) {
        setState(171);
        match(sysy2022Parser::T__5);
        setState(175);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295788544) != 0)) {
          setState(172);
          expr();
          setState(177);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(178);
        match(sysy2022Parser::T__6);
        setState(183);
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
  enterRule(_localctx, 22, sysy2022Parser::RuleBlock);
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
    setState(186);
    match(sysy2022Parser::T__8);
    setState(190);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120296788494) != 0)) {
      setState(187);
      blockItem();
      setState(192);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(193);
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
  enterRule(_localctx, 24, sysy2022Parser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(197);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__0:
      case sysy2022Parser::T__1:
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(195);
        decl();
        break;
      }

      case sysy2022Parser::T__8:
      case sysy2022Parser::T__11:
      case sysy2022Parser::T__13:
      case sysy2022Parser::T__15:
      case sysy2022Parser::T__16:
      case sysy2022Parser::T__17:
      case sysy2022Parser::T__18:
      case sysy2022Parser::T__19:
      case sysy2022Parser::T__20:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 2);
        setState(196);
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

sysy2022Parser::LValContext* sysy2022Parser::StmtContext::lVal() {
  return getRuleContext<sysy2022Parser::LValContext>(0);
}

sysy2022Parser::ExprContext* sysy2022Parser::StmtContext::expr() {
  return getRuleContext<sysy2022Parser::ExprContext>(0);
}

sysy2022Parser::BlockContext* sysy2022Parser::StmtContext::block() {
  return getRuleContext<sysy2022Parser::BlockContext>(0);
}

sysy2022Parser::CondContext* sysy2022Parser::StmtContext::cond() {
  return getRuleContext<sysy2022Parser::CondContext>(0);
}

std::vector<sysy2022Parser::StmtContext *> sysy2022Parser::StmtContext::stmt() {
  return getRuleContexts<sysy2022Parser::StmtContext>();
}

sysy2022Parser::StmtContext* sysy2022Parser::StmtContext::stmt(size_t i) {
  return getRuleContext<sysy2022Parser::StmtContext>(i);
}


size_t sysy2022Parser::StmtContext::getRuleIndex() const {
  return sysy2022Parser::RuleStmt;
}


std::any sysy2022Parser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::StmtContext* sysy2022Parser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 26, sysy2022Parser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(199);
      lVal();
      setState(200);
      match(sysy2022Parser::T__7);
      setState(201);
      expr();
      setState(202);
      match(sysy2022Parser::T__4);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(204);
      expr();
      setState(205);
      match(sysy2022Parser::T__4);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(207);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(208);
      match(sysy2022Parser::T__13);
      setState(209);
      match(sysy2022Parser::T__11);
      setState(210);
      cond();
      setState(211);
      match(sysy2022Parser::T__12);
      setState(212);
      stmt();
      setState(215);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(213);
        match(sysy2022Parser::T__14);
        setState(214);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(217);
      match(sysy2022Parser::T__15);
      setState(218);
      match(sysy2022Parser::T__11);
      setState(219);
      cond();
      setState(220);
      match(sysy2022Parser::T__12);
      setState(221);
      stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(223);
      match(sysy2022Parser::T__16);
      setState(224);
      match(sysy2022Parser::T__4);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(225);
      match(sysy2022Parser::T__17);
      setState(226);
      match(sysy2022Parser::T__4);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(227);
      match(sysy2022Parser::T__18);
      setState(229);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120295788544) != 0)) {
        setState(228);
        expr();
      }
      setState(231);
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

sysy2022Parser::AddExprContext* sysy2022Parser::ExprContext::addExpr() {
  return getRuleContext<sysy2022Parser::AddExprContext>(0);
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
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 28, sysy2022Parser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    addExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExprContext ------------------------------------------------------------------

sysy2022Parser::AddExprContext::AddExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::MulExprContext *> sysy2022Parser::AddExprContext::mulExpr() {
  return getRuleContexts<sysy2022Parser::MulExprContext>();
}

sysy2022Parser::MulExprContext* sysy2022Parser::AddExprContext::mulExpr(size_t i) {
  return getRuleContext<sysy2022Parser::MulExprContext>(i);
}


size_t sysy2022Parser::AddExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleAddExpr;
}


std::any sysy2022Parser::AddExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitAddExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::AddExprContext* sysy2022Parser::addExpr() {
  AddExprContext *_localctx = _tracker.createInstance<AddExprContext>(_ctx, getState());
  enterRule(_localctx, 30, sysy2022Parser::RuleAddExpr);
  size_t _la = 0;

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
    setState(236);
    mulExpr();
    setState(241);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(237);
        _la = _input->LA(1);
        if (!(_la == sysy2022Parser::T__19

        || _la == sysy2022Parser::T__20)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(238);
        mulExpr(); 
      }
      setState(243);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExprContext ------------------------------------------------------------------

sysy2022Parser::MulExprContext::MulExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::UnaryExprContext *> sysy2022Parser::MulExprContext::unaryExpr() {
  return getRuleContexts<sysy2022Parser::UnaryExprContext>();
}

sysy2022Parser::UnaryExprContext* sysy2022Parser::MulExprContext::unaryExpr(size_t i) {
  return getRuleContext<sysy2022Parser::UnaryExprContext>(i);
}


size_t sysy2022Parser::MulExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleMulExpr;
}


std::any sysy2022Parser::MulExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitMulExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::MulExprContext* sysy2022Parser::mulExpr() {
  MulExprContext *_localctx = _tracker.createInstance<MulExprContext>(_ctx, getState());
  enterRule(_localctx, 32, sysy2022Parser::RuleMulExpr);
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
    setState(244);
    unaryExpr();
    setState(249);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 29360128) != 0)) {
      setState(245);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 29360128) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(246);
      unaryExpr();
      setState(251);
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
    setState(262);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(252);
      primaryExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(253);
      match(sysy2022Parser::ID);
      setState(254);
      match(sysy2022Parser::T__11);
      setState(256);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120295788544) != 0)) {
        setState(255);
        funcRParams();
      }
      setState(258);
      match(sysy2022Parser::T__12);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(259);
      unaryOp();
      setState(260);
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
    setState(264);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 36700160) != 0))) {
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
    setState(266);
    expr();
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(267);
      match(sysy2022Parser::T__3);
      setState(268);
      expr();
      setState(273);
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
    setState(280);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__11: {
        enterOuterAlt(_localctx, 1);
        setState(274);
        match(sysy2022Parser::T__11);
        setState(275);
        expr();
        setState(276);
        match(sysy2022Parser::T__12);
        break;
      }

      case sysy2022Parser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(278);
        lVal();
        break;
      }

      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(279);
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
    setState(282);
    match(sysy2022Parser::ID);
    setState(289);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(283);
      match(sysy2022Parser::T__5);
      setState(284);
      expr();
      setState(285);
      match(sysy2022Parser::T__6);
      setState(291);
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
    setState(292);
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

sysy2022Parser::LOrExprContext* sysy2022Parser::CondContext::lOrExpr() {
  return getRuleContext<sysy2022Parser::LOrExprContext>(0);
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
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 46, sysy2022Parser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(294);
    lOrExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExprContext ------------------------------------------------------------------

sysy2022Parser::LOrExprContext::LOrExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::LAndExprContext *> sysy2022Parser::LOrExprContext::lAndExpr() {
  return getRuleContexts<sysy2022Parser::LAndExprContext>();
}

sysy2022Parser::LAndExprContext* sysy2022Parser::LOrExprContext::lAndExpr(size_t i) {
  return getRuleContext<sysy2022Parser::LAndExprContext>(i);
}


size_t sysy2022Parser::LOrExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleLOrExpr;
}


std::any sysy2022Parser::LOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitLOrExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::LOrExprContext* sysy2022Parser::lOrExpr() {
  LOrExprContext *_localctx = _tracker.createInstance<LOrExprContext>(_ctx, getState());
  enterRule(_localctx, 48, sysy2022Parser::RuleLOrExpr);
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
    setState(296);
    lAndExpr();
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__25) {
      setState(297);
      match(sysy2022Parser::T__25);
      setState(298);
      lAndExpr();
      setState(303);
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

//----------------- LAndExprContext ------------------------------------------------------------------

sysy2022Parser::LAndExprContext::LAndExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::EqExprContext *> sysy2022Parser::LAndExprContext::eqExpr() {
  return getRuleContexts<sysy2022Parser::EqExprContext>();
}

sysy2022Parser::EqExprContext* sysy2022Parser::LAndExprContext::eqExpr(size_t i) {
  return getRuleContext<sysy2022Parser::EqExprContext>(i);
}


size_t sysy2022Parser::LAndExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleLAndExpr;
}


std::any sysy2022Parser::LAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitLAndExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::LAndExprContext* sysy2022Parser::lAndExpr() {
  LAndExprContext *_localctx = _tracker.createInstance<LAndExprContext>(_ctx, getState());
  enterRule(_localctx, 50, sysy2022Parser::RuleLAndExpr);
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
    setState(304);
    eqExpr();
    setState(309);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__26) {
      setState(305);
      match(sysy2022Parser::T__26);
      setState(306);
      eqExpr();
      setState(311);
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

//----------------- EqExprContext ------------------------------------------------------------------

sysy2022Parser::EqExprContext::EqExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::RelExprContext *> sysy2022Parser::EqExprContext::relExpr() {
  return getRuleContexts<sysy2022Parser::RelExprContext>();
}

sysy2022Parser::RelExprContext* sysy2022Parser::EqExprContext::relExpr(size_t i) {
  return getRuleContext<sysy2022Parser::RelExprContext>(i);
}


size_t sysy2022Parser::EqExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleEqExpr;
}


std::any sysy2022Parser::EqExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitEqExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::EqExprContext* sysy2022Parser::eqExpr() {
  EqExprContext *_localctx = _tracker.createInstance<EqExprContext>(_ctx, getState());
  enterRule(_localctx, 52, sysy2022Parser::RuleEqExpr);
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
    setState(312);
    relExpr();
    setState(317);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__27

    || _la == sysy2022Parser::T__28) {
      setState(313);
      _la = _input->LA(1);
      if (!(_la == sysy2022Parser::T__27

      || _la == sysy2022Parser::T__28)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(314);
      relExpr();
      setState(319);
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

//----------------- RelExprContext ------------------------------------------------------------------

sysy2022Parser::RelExprContext::RelExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<sysy2022Parser::AddExprContext *> sysy2022Parser::RelExprContext::addExpr() {
  return getRuleContexts<sysy2022Parser::AddExprContext>();
}

sysy2022Parser::AddExprContext* sysy2022Parser::RelExprContext::addExpr(size_t i) {
  return getRuleContext<sysy2022Parser::AddExprContext>(i);
}


size_t sysy2022Parser::RelExprContext::getRuleIndex() const {
  return sysy2022Parser::RuleRelExpr;
}


std::any sysy2022Parser::RelExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<sysy2022Visitor*>(visitor))
    return parserVisitor->visitRelExpr(this);
  else
    return visitor->visitChildren(this);
}

sysy2022Parser::RelExprContext* sysy2022Parser::relExpr() {
  RelExprContext *_localctx = _tracker.createInstance<RelExprContext>(_ctx, getState());
  enterRule(_localctx, 54, sysy2022Parser::RuleRelExpr);
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
    setState(320);
    addExpr();
    setState(325);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16106127360) != 0)) {
      setState(321);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16106127360) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(322);
      addExpr();
      setState(327);
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

//----------------- ConstExprContext ------------------------------------------------------------------

sysy2022Parser::ConstExprContext::ConstExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

sysy2022Parser::AddExprContext* sysy2022Parser::ConstExprContext::addExpr() {
  return getRuleContext<sysy2022Parser::AddExprContext>(0);
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
  enterRule(_localctx, 56, sysy2022Parser::RuleConstExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    addExpr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void sysy2022Parser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sysy2022ParserInitialize();
#else
  ::antlr4::internal::call_once(sysy2022ParserOnceFlag, sysy2022ParserInitialize);
#endif
}
