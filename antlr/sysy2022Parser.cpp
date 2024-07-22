
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
      "funcFParam", "block", "blockItem", "stmt", "expr", "addExpr", "mulExpr", 
      "unaryExpr", "unaryOp", "funcRParams", "primaryExpr", "lVal", "number", 
      "cond", "lOrExpr", "lAndExpr", "eqExpr", "relExpr", "constExpr"
    },
    std::vector<std::string>{
      "", "'int'", "'float'", "'const'", "','", "';'", "'['", "']'", "'='", 
      "'{'", "'}'", "'('", "')'", "'void'", "'if'", "'else'", "'while'", 
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
  	4,1,39,339,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,5,0,65,8,0,10,0,12,0,68,9,0,1,0,1,0,1,
  	1,1,1,3,1,74,8,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,5,3,83,8,3,10,3,12,3,86,
  	9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,95,8,4,10,4,12,4,98,9,4,1,4,1,4,1,
  	4,1,5,1,5,1,5,1,5,1,5,5,5,108,8,5,10,5,12,5,111,9,5,3,5,113,8,5,1,5,3,
  	5,116,8,5,1,6,1,6,1,6,1,6,5,6,122,8,6,10,6,12,6,125,9,6,1,6,1,6,1,7,1,
  	7,1,7,1,7,1,7,5,7,134,8,7,10,7,12,7,137,9,7,1,7,1,7,1,7,1,8,1,8,1,8,1,
  	8,1,8,5,8,147,8,8,10,8,12,8,150,9,8,3,8,152,8,8,1,8,3,8,155,8,8,1,9,1,
  	9,1,9,1,9,3,9,161,8,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,5,11,171,8,
  	11,10,11,12,11,174,9,11,1,12,1,12,1,12,1,12,1,12,1,12,5,12,182,8,12,10,
  	12,12,12,185,9,12,1,12,5,12,188,8,12,10,12,12,12,191,9,12,3,12,193,8,
  	12,1,13,1,13,5,13,197,8,13,10,13,12,13,200,9,13,1,13,1,13,1,14,1,14,3,
  	14,206,8,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,15,3,15,224,8,15,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,15,1,15,3,15,238,8,15,1,15,3,15,241,8,15,1,16,1,16,
  	1,17,1,17,1,17,5,17,248,8,17,10,17,12,17,251,9,17,1,18,1,18,1,18,5,18,
  	256,8,18,10,18,12,18,259,9,18,1,19,1,19,1,19,1,19,3,19,265,8,19,1,19,
  	1,19,1,19,1,19,3,19,271,8,19,1,20,1,20,1,21,1,21,1,21,5,21,278,8,21,10,
  	21,12,21,281,9,21,1,22,1,22,1,22,1,22,1,22,1,22,3,22,289,8,22,1,23,1,
  	23,1,23,1,23,1,23,5,23,296,8,23,10,23,12,23,299,9,23,1,24,1,24,1,25,1,
  	25,1,26,1,26,1,26,5,26,308,8,26,10,26,12,26,311,9,26,1,27,1,27,1,27,5,
  	27,316,8,27,10,27,12,27,319,9,27,1,28,1,28,1,28,5,28,324,8,28,10,28,12,
  	28,327,9,28,1,29,1,29,1,29,5,29,332,8,29,10,29,12,29,335,9,29,1,30,1,
  	30,1,30,0,0,31,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,44,46,48,50,52,54,56,58,60,0,8,1,0,1,2,2,0,1,2,13,13,1,0,20,21,
  	1,0,22,24,2,0,20,21,25,25,1,0,35,36,1,0,28,29,1,0,30,33,349,0,66,1,0,
  	0,0,2,73,1,0,0,0,4,75,1,0,0,0,6,77,1,0,0,0,8,89,1,0,0,0,10,115,1,0,0,
  	0,12,117,1,0,0,0,14,128,1,0,0,0,16,154,1,0,0,0,18,156,1,0,0,0,20,165,
  	1,0,0,0,22,167,1,0,0,0,24,175,1,0,0,0,26,194,1,0,0,0,28,205,1,0,0,0,30,
  	240,1,0,0,0,32,242,1,0,0,0,34,244,1,0,0,0,36,252,1,0,0,0,38,270,1,0,0,
  	0,40,272,1,0,0,0,42,274,1,0,0,0,44,288,1,0,0,0,46,290,1,0,0,0,48,300,
  	1,0,0,0,50,302,1,0,0,0,52,304,1,0,0,0,54,312,1,0,0,0,56,320,1,0,0,0,58,
  	328,1,0,0,0,60,336,1,0,0,0,62,65,3,2,1,0,63,65,3,18,9,0,64,62,1,0,0,0,
  	64,63,1,0,0,0,65,68,1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,69,1,0,0,0,
  	68,66,1,0,0,0,69,70,5,0,0,1,70,1,1,0,0,0,71,74,3,6,3,0,72,74,3,12,6,0,
  	73,71,1,0,0,0,73,72,1,0,0,0,74,3,1,0,0,0,75,76,7,0,0,0,76,5,1,0,0,0,77,
  	78,5,3,0,0,78,79,3,4,2,0,79,84,3,8,4,0,80,81,5,4,0,0,81,83,3,8,4,0,82,
  	80,1,0,0,0,83,86,1,0,0,0,84,82,1,0,0,0,84,85,1,0,0,0,85,87,1,0,0,0,86,
  	84,1,0,0,0,87,88,5,5,0,0,88,7,1,0,0,0,89,96,5,34,0,0,90,91,5,6,0,0,91,
  	92,3,60,30,0,92,93,5,7,0,0,93,95,1,0,0,0,94,90,1,0,0,0,95,98,1,0,0,0,
  	96,94,1,0,0,0,96,97,1,0,0,0,97,99,1,0,0,0,98,96,1,0,0,0,99,100,5,8,0,
  	0,100,101,3,10,5,0,101,9,1,0,0,0,102,116,3,60,30,0,103,112,5,9,0,0,104,
  	109,3,10,5,0,105,106,5,4,0,0,106,108,3,10,5,0,107,105,1,0,0,0,108,111,
  	1,0,0,0,109,107,1,0,0,0,109,110,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,
  	0,112,104,1,0,0,0,112,113,1,0,0,0,113,114,1,0,0,0,114,116,5,10,0,0,115,
  	102,1,0,0,0,115,103,1,0,0,0,116,11,1,0,0,0,117,118,3,4,2,0,118,123,3,
  	14,7,0,119,120,5,4,0,0,120,122,3,14,7,0,121,119,1,0,0,0,122,125,1,0,0,
  	0,123,121,1,0,0,0,123,124,1,0,0,0,124,126,1,0,0,0,125,123,1,0,0,0,126,
  	127,5,5,0,0,127,13,1,0,0,0,128,135,5,34,0,0,129,130,5,6,0,0,130,131,3,
  	60,30,0,131,132,5,7,0,0,132,134,1,0,0,0,133,129,1,0,0,0,134,137,1,0,0,
  	0,135,133,1,0,0,0,135,136,1,0,0,0,136,138,1,0,0,0,137,135,1,0,0,0,138,
  	139,5,8,0,0,139,140,3,16,8,0,140,15,1,0,0,0,141,155,3,32,16,0,142,151,
  	5,9,0,0,143,148,3,16,8,0,144,145,5,4,0,0,145,147,3,16,8,0,146,144,1,0,
  	0,0,147,150,1,0,0,0,148,146,1,0,0,0,148,149,1,0,0,0,149,152,1,0,0,0,150,
  	148,1,0,0,0,151,143,1,0,0,0,151,152,1,0,0,0,152,153,1,0,0,0,153,155,5,
  	10,0,0,154,141,1,0,0,0,154,142,1,0,0,0,155,17,1,0,0,0,156,157,3,20,10,
  	0,157,158,5,34,0,0,158,160,5,11,0,0,159,161,3,22,11,0,160,159,1,0,0,0,
  	160,161,1,0,0,0,161,162,1,0,0,0,162,163,5,12,0,0,163,164,3,26,13,0,164,
  	19,1,0,0,0,165,166,7,1,0,0,166,21,1,0,0,0,167,172,3,24,12,0,168,169,5,
  	4,0,0,169,171,3,24,12,0,170,168,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,
  	0,172,173,1,0,0,0,173,23,1,0,0,0,174,172,1,0,0,0,175,176,3,4,2,0,176,
  	192,5,34,0,0,177,178,5,6,0,0,178,189,5,7,0,0,179,183,5,6,0,0,180,182,
  	3,32,16,0,181,180,1,0,0,0,182,185,1,0,0,0,183,181,1,0,0,0,183,184,1,0,
  	0,0,184,186,1,0,0,0,185,183,1,0,0,0,186,188,5,7,0,0,187,179,1,0,0,0,188,
  	191,1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,190,193,1,0,0,0,191,189,1,
  	0,0,0,192,177,1,0,0,0,192,193,1,0,0,0,193,25,1,0,0,0,194,198,5,9,0,0,
  	195,197,3,28,14,0,196,195,1,0,0,0,197,200,1,0,0,0,198,196,1,0,0,0,198,
  	199,1,0,0,0,199,201,1,0,0,0,200,198,1,0,0,0,201,202,5,10,0,0,202,27,1,
  	0,0,0,203,206,3,2,1,0,204,206,3,30,15,0,205,203,1,0,0,0,205,204,1,0,0,
  	0,206,29,1,0,0,0,207,208,3,46,23,0,208,209,5,8,0,0,209,210,3,32,16,0,
  	210,211,5,5,0,0,211,241,1,0,0,0,212,213,3,32,16,0,213,214,5,5,0,0,214,
  	241,1,0,0,0,215,241,3,26,13,0,216,217,5,14,0,0,217,218,5,11,0,0,218,219,
  	3,50,25,0,219,220,5,12,0,0,220,223,3,30,15,0,221,222,5,15,0,0,222,224,
  	3,30,15,0,223,221,1,0,0,0,223,224,1,0,0,0,224,241,1,0,0,0,225,226,5,16,
  	0,0,226,227,5,11,0,0,227,228,3,50,25,0,228,229,5,12,0,0,229,230,3,30,
  	15,0,230,241,1,0,0,0,231,232,5,17,0,0,232,241,5,5,0,0,233,234,5,18,0,
  	0,234,241,5,5,0,0,235,237,5,19,0,0,236,238,3,32,16,0,237,236,1,0,0,0,
  	237,238,1,0,0,0,238,239,1,0,0,0,239,241,5,5,0,0,240,207,1,0,0,0,240,212,
  	1,0,0,0,240,215,1,0,0,0,240,216,1,0,0,0,240,225,1,0,0,0,240,231,1,0,0,
  	0,240,233,1,0,0,0,240,235,1,0,0,0,241,31,1,0,0,0,242,243,3,34,17,0,243,
  	33,1,0,0,0,244,249,3,36,18,0,245,246,7,2,0,0,246,248,3,36,18,0,247,245,
  	1,0,0,0,248,251,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,35,1,0,0,
  	0,251,249,1,0,0,0,252,257,3,38,19,0,253,254,7,3,0,0,254,256,3,38,19,0,
  	255,253,1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,257,258,1,0,0,0,258,37,
  	1,0,0,0,259,257,1,0,0,0,260,271,3,44,22,0,261,262,5,34,0,0,262,264,5,
  	11,0,0,263,265,3,42,21,0,264,263,1,0,0,0,264,265,1,0,0,0,265,266,1,0,
  	0,0,266,271,5,12,0,0,267,268,3,40,20,0,268,269,3,38,19,0,269,271,1,0,
  	0,0,270,260,1,0,0,0,270,261,1,0,0,0,270,267,1,0,0,0,271,39,1,0,0,0,272,
  	273,7,4,0,0,273,41,1,0,0,0,274,279,3,32,16,0,275,276,5,4,0,0,276,278,
  	3,32,16,0,277,275,1,0,0,0,278,281,1,0,0,0,279,277,1,0,0,0,279,280,1,0,
  	0,0,280,43,1,0,0,0,281,279,1,0,0,0,282,283,5,11,0,0,283,284,3,32,16,0,
  	284,285,5,12,0,0,285,289,1,0,0,0,286,289,3,46,23,0,287,289,3,48,24,0,
  	288,282,1,0,0,0,288,286,1,0,0,0,288,287,1,0,0,0,289,45,1,0,0,0,290,297,
  	5,34,0,0,291,292,5,6,0,0,292,293,3,32,16,0,293,294,5,7,0,0,294,296,1,
  	0,0,0,295,291,1,0,0,0,296,299,1,0,0,0,297,295,1,0,0,0,297,298,1,0,0,0,
  	298,47,1,0,0,0,299,297,1,0,0,0,300,301,7,5,0,0,301,49,1,0,0,0,302,303,
  	3,52,26,0,303,51,1,0,0,0,304,309,3,54,27,0,305,306,5,26,0,0,306,308,3,
  	54,27,0,307,305,1,0,0,0,308,311,1,0,0,0,309,307,1,0,0,0,309,310,1,0,0,
  	0,310,53,1,0,0,0,311,309,1,0,0,0,312,317,3,56,28,0,313,314,5,27,0,0,314,
  	316,3,56,28,0,315,313,1,0,0,0,316,319,1,0,0,0,317,315,1,0,0,0,317,318,
  	1,0,0,0,318,55,1,0,0,0,319,317,1,0,0,0,320,325,3,58,29,0,321,322,7,6,
  	0,0,322,324,3,58,29,0,323,321,1,0,0,0,324,327,1,0,0,0,325,323,1,0,0,0,
  	325,326,1,0,0,0,326,57,1,0,0,0,327,325,1,0,0,0,328,333,3,34,17,0,329,
  	330,7,7,0,0,330,332,3,34,17,0,331,329,1,0,0,0,332,335,1,0,0,0,333,331,
  	1,0,0,0,333,334,1,0,0,0,334,59,1,0,0,0,335,333,1,0,0,0,336,337,3,34,17,
  	0,337,61,1,0,0,0,34,64,66,73,84,96,109,112,115,123,135,148,151,154,160,
  	172,183,189,192,198,205,223,237,240,249,257,264,270,279,288,297,309,317,
  	325,333
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
    setState(66);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8206) != 0)) {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(62);
        decl();
        break;
      }

      case 2: {
        setState(63);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(69);
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
    setState(73);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(71);
        constDecl();
        break;
      }

      case sysy2022Parser::T__0:
      case sysy2022Parser::T__1: {
        enterOuterAlt(_localctx, 2);
        setState(72);
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
    setState(75);
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
    setState(77);
    match(sysy2022Parser::T__2);
    setState(78);
    basicType();
    setState(79);
    constDef();
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(80);
      match(sysy2022Parser::T__3);
      setState(81);
      constDef();
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(87);
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
    setState(89);
    match(sysy2022Parser::ID);
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(90);
      match(sysy2022Parser::T__5);
      setState(91);
      constExpr();
      setState(92);
      match(sysy2022Parser::T__6);
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
    match(sysy2022Parser::T__7);
    setState(100);
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
    setState(115);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10:
      case sysy2022Parser::T__19:
      case sysy2022Parser::T__20:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(102);
        constExpr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(103);
        match(sysy2022Parser::T__8);
        setState(112);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295787008) != 0)) {
          setState(104);
          constInitVal();
          setState(109);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(105);
            match(sysy2022Parser::T__3);
            setState(106);
            constInitVal();
            setState(111);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(114);
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
    setState(117);
    basicType();
    setState(118);
    varDef();
    setState(123);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(119);
      match(sysy2022Parser::T__3);
      setState(120);
      varDef();
      setState(125);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(126);
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
    setState(128);
    match(sysy2022Parser::ID);
    setState(135);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(129);
      match(sysy2022Parser::T__5);
      setState(130);
      constExpr();
      setState(131);
      match(sysy2022Parser::T__6);
      setState(137);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(138);
    match(sysy2022Parser::T__7);
    setState(139);
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
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10:
      case sysy2022Parser::T__19:
      case sysy2022Parser::T__20:
      case sysy2022Parser::T__24:
      case sysy2022Parser::ID:
      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(141);
        expr();
        break;
      }

      case sysy2022Parser::T__8: {
        enterOuterAlt(_localctx, 2);
        setState(142);
        match(sysy2022Parser::T__8);
        setState(151);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295787008) != 0)) {
          setState(143);
          initVal();
          setState(148);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == sysy2022Parser::T__3) {
            setState(144);
            match(sysy2022Parser::T__3);
            setState(145);
            initVal();
            setState(150);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(153);
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
    setState(156);
    funcType();
    setState(157);
    match(sysy2022Parser::ID);
    setState(158);
    match(sysy2022Parser::T__10);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__0

    || _la == sysy2022Parser::T__1) {
      setState(159);
      funcFParams();
    }
    setState(162);
    match(sysy2022Parser::T__11);
    setState(163);
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
    setState(165);
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
    setState(167);
    funcFParam();
    setState(172);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(168);
      match(sysy2022Parser::T__3);
      setState(169);
      funcFParam();
      setState(174);
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
    setState(175);
    basicType();
    setState(176);
    match(sysy2022Parser::ID);
    setState(192);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == sysy2022Parser::T__5) {
      setState(177);
      match(sysy2022Parser::T__5);
      setState(178);
      match(sysy2022Parser::T__6);
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == sysy2022Parser::T__5) {
        setState(179);
        match(sysy2022Parser::T__5);
        setState(183);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120295786496) != 0)) {
          setState(180);
          expr();
          setState(185);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(186);
        match(sysy2022Parser::T__6);
        setState(191);
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
    setState(194);
    match(sysy2022Parser::T__8);
    setState(198);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 120296786446) != 0)) {
      setState(195);
      blockItem();
      setState(200);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(201);
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
    setState(205);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__0:
      case sysy2022Parser::T__1:
      case sysy2022Parser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(203);
        decl();
        break;
      }

      case sysy2022Parser::T__8:
      case sysy2022Parser::T__10:
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
        setState(204);
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
    setState(240);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<sysy2022Parser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(207);
      lVal();
      setState(208);
      match(sysy2022Parser::T__7);
      setState(209);
      expr();
      setState(210);
      match(sysy2022Parser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<sysy2022Parser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(212);
      expr();
      setState(213);
      match(sysy2022Parser::T__4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<sysy2022Parser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(215);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<sysy2022Parser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(216);
      match(sysy2022Parser::T__13);
      setState(217);
      match(sysy2022Parser::T__10);
      setState(218);
      cond();
      setState(219);
      match(sysy2022Parser::T__11);
      setState(220);
      stmt();
      setState(223);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
      case 1: {
        setState(221);
        match(sysy2022Parser::T__14);
        setState(222);
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
      setState(225);
      match(sysy2022Parser::T__15);
      setState(226);
      match(sysy2022Parser::T__10);
      setState(227);
      cond();
      setState(228);
      match(sysy2022Parser::T__11);
      setState(229);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<sysy2022Parser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(231);
      match(sysy2022Parser::T__16);
      setState(232);
      match(sysy2022Parser::T__4);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<sysy2022Parser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(233);
      match(sysy2022Parser::T__17);
      setState(234);
      match(sysy2022Parser::T__4);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<sysy2022Parser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(235);
      match(sysy2022Parser::T__18);
      setState(237);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120295786496) != 0)) {
        setState(236);
        expr();
      }
      setState(239);
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
  enterRule(_localctx, 32, sysy2022Parser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
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
  enterRule(_localctx, 34, sysy2022Parser::RuleAddExpr);
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
    setState(244);
    mulExpr();
    setState(249);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(245);
        _la = _input->LA(1);
        if (!(_la == sysy2022Parser::T__19

        || _la == sysy2022Parser::T__20)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(246);
        mulExpr(); 
      }
      setState(251);
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
  enterRule(_localctx, 36, sysy2022Parser::RuleMulExpr);
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
    setState(252);
    unaryExpr();
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 29360128) != 0)) {
      setState(253);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 29360128) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(254);
      unaryExpr();
      setState(259);
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
  enterRule(_localctx, 38, sysy2022Parser::RuleUnaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(260);
      primaryExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(261);
      match(sysy2022Parser::ID);
      setState(262);
      match(sysy2022Parser::T__10);
      setState(264);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120295786496) != 0)) {
        setState(263);
        funcRParams();
      }
      setState(266);
      match(sysy2022Parser::T__11);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(267);
      unaryOp();
      setState(268);
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
  enterRule(_localctx, 40, sysy2022Parser::RuleUnaryOp);
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
    setState(272);
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
  enterRule(_localctx, 42, sysy2022Parser::RuleFuncRParams);
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
    setState(274);
    expr();
    setState(279);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__3) {
      setState(275);
      match(sysy2022Parser::T__3);
      setState(276);
      expr();
      setState(281);
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
  enterRule(_localctx, 44, sysy2022Parser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(288);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case sysy2022Parser::T__10: {
        enterOuterAlt(_localctx, 1);
        setState(282);
        match(sysy2022Parser::T__10);
        setState(283);
        expr();
        setState(284);
        match(sysy2022Parser::T__11);
        break;
      }

      case sysy2022Parser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(286);
        lVal();
        break;
      }

      case sysy2022Parser::INT:
      case sysy2022Parser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(287);
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
  enterRule(_localctx, 46, sysy2022Parser::RuleLVal);
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
    setState(290);
    match(sysy2022Parser::ID);
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__5) {
      setState(291);
      match(sysy2022Parser::T__5);
      setState(292);
      expr();
      setState(293);
      match(sysy2022Parser::T__6);
      setState(299);
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
  enterRule(_localctx, 48, sysy2022Parser::RuleNumber);
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
    setState(300);
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
  enterRule(_localctx, 50, sysy2022Parser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
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
  enterRule(_localctx, 52, sysy2022Parser::RuleLOrExpr);
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
    lAndExpr();
    setState(309);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__25) {
      setState(305);
      match(sysy2022Parser::T__25);
      setState(306);
      lAndExpr();
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
  enterRule(_localctx, 54, sysy2022Parser::RuleLAndExpr);
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
    eqExpr();
    setState(317);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__26) {
      setState(313);
      match(sysy2022Parser::T__26);
      setState(314);
      eqExpr();
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
  enterRule(_localctx, 56, sysy2022Parser::RuleEqExpr);
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
    relExpr();
    setState(325);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == sysy2022Parser::T__27

    || _la == sysy2022Parser::T__28) {
      setState(321);
      _la = _input->LA(1);
      if (!(_la == sysy2022Parser::T__27

      || _la == sysy2022Parser::T__28)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(322);
      relExpr();
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
  enterRule(_localctx, 58, sysy2022Parser::RuleRelExpr);
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
    setState(328);
    addExpr();
    setState(333);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16106127360) != 0)) {
      setState(329);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 16106127360) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(330);
      addExpr();
      setState(335);
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
  enterRule(_localctx, 60, sysy2022Parser::RuleConstExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
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
