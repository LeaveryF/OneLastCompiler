
// Generated from sysy2022.g4 by ANTLR 4.13.1


#include "sysy2022Lexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct Sysy2022LexerStaticData final {
  Sysy2022LexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  Sysy2022LexerStaticData(const Sysy2022LexerStaticData&) = delete;
  Sysy2022LexerStaticData(Sysy2022LexerStaticData&&) = delete;
  Sysy2022LexerStaticData& operator=(const Sysy2022LexerStaticData&) = delete;
  Sysy2022LexerStaticData& operator=(Sysy2022LexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysy2022lexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
Sysy2022LexerStaticData *sysy2022lexerLexerStaticData = nullptr;

void sysy2022lexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sysy2022lexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(sysy2022lexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<Sysy2022LexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "T__26", "T__27", "T__28", "T__29", "T__30", "T__31", "T__32", 
      "ID", "INT", "FLOAT", "DecimalFloatingConstant", "ExponentPart", "HexadecimalFloatingConstant", 
      "BinaryExponentPart", "BlockComment", "LineComment", "Blank"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,39,344,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,
  	1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,
  	1,25,1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,28,1,29,1,29,1,30,1,30,
  	1,31,1,31,1,31,1,32,1,32,1,32,1,33,1,33,5,33,199,8,33,10,33,12,33,202,
  	9,33,1,34,1,34,5,34,206,8,34,10,34,12,34,209,9,34,1,34,1,34,5,34,213,
  	8,34,10,34,12,34,216,9,34,1,34,1,34,1,34,4,34,221,8,34,11,34,12,34,222,
  	3,34,225,8,34,1,35,1,35,3,35,229,8,35,1,36,4,36,232,8,36,11,36,12,36,
  	233,1,36,1,36,4,36,238,8,36,11,36,12,36,239,1,36,4,36,243,8,36,11,36,
  	12,36,244,1,36,3,36,248,8,36,1,36,3,36,251,8,36,1,36,4,36,254,8,36,11,
  	36,12,36,255,1,36,3,36,259,8,36,1,37,1,37,3,37,263,8,37,1,37,4,37,266,
  	8,37,11,37,12,37,267,1,38,1,38,1,38,4,38,273,8,38,11,38,12,38,274,1,38,
  	1,38,4,38,279,8,38,11,38,12,38,280,1,38,4,38,284,8,38,11,38,12,38,285,
  	1,38,3,38,289,8,38,1,38,3,38,292,8,38,1,38,1,38,1,38,4,38,297,8,38,11,
  	38,12,38,298,1,38,3,38,302,8,38,1,39,1,39,3,39,306,8,39,1,39,4,39,309,
  	8,39,11,39,12,39,310,1,40,1,40,1,40,1,40,5,40,317,8,40,10,40,12,40,320,
  	9,40,1,40,1,40,1,40,1,40,1,40,1,41,1,41,1,41,1,41,5,41,331,8,41,10,41,
  	12,41,334,9,41,1,41,1,41,1,42,4,42,339,8,42,11,42,12,42,340,1,42,1,42,
  	3,233,274,318,0,43,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,
  	23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,
  	69,35,71,36,73,0,75,0,77,0,79,0,81,37,83,38,85,39,1,0,12,3,0,65,90,95,
  	95,97,122,4,0,48,57,65,90,95,95,97,122,1,0,49,57,1,0,48,57,1,0,48,55,
  	2,0,88,88,120,120,3,0,48,57,65,70,97,102,2,0,69,69,101,101,2,0,43,43,
  	45,45,2,0,80,80,112,112,2,0,10,10,13,13,3,0,9,10,13,13,32,32,367,0,1,
  	1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,
  	0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,
  	1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,
  	0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,
  	0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,
  	1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,
  	0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,0,0,81,1,0,0,0,0,83,1,0,0,0,
  	0,85,1,0,0,0,1,87,1,0,0,0,3,91,1,0,0,0,5,97,1,0,0,0,7,103,1,0,0,0,9,105,
  	1,0,0,0,11,107,1,0,0,0,13,109,1,0,0,0,15,111,1,0,0,0,17,113,1,0,0,0,19,
  	115,1,0,0,0,21,117,1,0,0,0,23,119,1,0,0,0,25,121,1,0,0,0,27,126,1,0,0,
  	0,29,129,1,0,0,0,31,134,1,0,0,0,33,140,1,0,0,0,35,146,1,0,0,0,37,155,
  	1,0,0,0,39,162,1,0,0,0,41,164,1,0,0,0,43,166,1,0,0,0,45,168,1,0,0,0,47,
  	170,1,0,0,0,49,172,1,0,0,0,51,174,1,0,0,0,53,177,1,0,0,0,55,180,1,0,0,
  	0,57,183,1,0,0,0,59,186,1,0,0,0,61,188,1,0,0,0,63,190,1,0,0,0,65,193,
  	1,0,0,0,67,196,1,0,0,0,69,224,1,0,0,0,71,228,1,0,0,0,73,258,1,0,0,0,75,
  	260,1,0,0,0,77,301,1,0,0,0,79,303,1,0,0,0,81,312,1,0,0,0,83,326,1,0,0,
  	0,85,338,1,0,0,0,87,88,5,105,0,0,88,89,5,110,0,0,89,90,5,116,0,0,90,2,
  	1,0,0,0,91,92,5,102,0,0,92,93,5,108,0,0,93,94,5,111,0,0,94,95,5,97,0,
  	0,95,96,5,116,0,0,96,4,1,0,0,0,97,98,5,99,0,0,98,99,5,111,0,0,99,100,
  	5,110,0,0,100,101,5,115,0,0,101,102,5,116,0,0,102,6,1,0,0,0,103,104,5,
  	44,0,0,104,8,1,0,0,0,105,106,5,59,0,0,106,10,1,0,0,0,107,108,5,91,0,0,
  	108,12,1,0,0,0,109,110,5,93,0,0,110,14,1,0,0,0,111,112,5,61,0,0,112,16,
  	1,0,0,0,113,114,5,123,0,0,114,18,1,0,0,0,115,116,5,125,0,0,116,20,1,0,
  	0,0,117,118,5,40,0,0,118,22,1,0,0,0,119,120,5,41,0,0,120,24,1,0,0,0,121,
  	122,5,118,0,0,122,123,5,111,0,0,123,124,5,105,0,0,124,125,5,100,0,0,125,
  	26,1,0,0,0,126,127,5,105,0,0,127,128,5,102,0,0,128,28,1,0,0,0,129,130,
  	5,101,0,0,130,131,5,108,0,0,131,132,5,115,0,0,132,133,5,101,0,0,133,30,
  	1,0,0,0,134,135,5,119,0,0,135,136,5,104,0,0,136,137,5,105,0,0,137,138,
  	5,108,0,0,138,139,5,101,0,0,139,32,1,0,0,0,140,141,5,98,0,0,141,142,5,
  	114,0,0,142,143,5,101,0,0,143,144,5,97,0,0,144,145,5,107,0,0,145,34,1,
  	0,0,0,146,147,5,99,0,0,147,148,5,111,0,0,148,149,5,110,0,0,149,150,5,
  	116,0,0,150,151,5,105,0,0,151,152,5,110,0,0,152,153,5,117,0,0,153,154,
  	5,101,0,0,154,36,1,0,0,0,155,156,5,114,0,0,156,157,5,101,0,0,157,158,
  	5,116,0,0,158,159,5,117,0,0,159,160,5,114,0,0,160,161,5,110,0,0,161,38,
  	1,0,0,0,162,163,5,43,0,0,163,40,1,0,0,0,164,165,5,45,0,0,165,42,1,0,0,
  	0,166,167,5,42,0,0,167,44,1,0,0,0,168,169,5,47,0,0,169,46,1,0,0,0,170,
  	171,5,37,0,0,171,48,1,0,0,0,172,173,5,33,0,0,173,50,1,0,0,0,174,175,5,
  	124,0,0,175,176,5,124,0,0,176,52,1,0,0,0,177,178,5,38,0,0,178,179,5,38,
  	0,0,179,54,1,0,0,0,180,181,5,61,0,0,181,182,5,61,0,0,182,56,1,0,0,0,183,
  	184,5,33,0,0,184,185,5,61,0,0,185,58,1,0,0,0,186,187,5,60,0,0,187,60,
  	1,0,0,0,188,189,5,62,0,0,189,62,1,0,0,0,190,191,5,60,0,0,191,192,5,61,
  	0,0,192,64,1,0,0,0,193,194,5,62,0,0,194,195,5,61,0,0,195,66,1,0,0,0,196,
  	200,7,0,0,0,197,199,7,1,0,0,198,197,1,0,0,0,199,202,1,0,0,0,200,198,1,
  	0,0,0,200,201,1,0,0,0,201,68,1,0,0,0,202,200,1,0,0,0,203,207,7,2,0,0,
  	204,206,7,3,0,0,205,204,1,0,0,0,206,209,1,0,0,0,207,205,1,0,0,0,207,208,
  	1,0,0,0,208,225,1,0,0,0,209,207,1,0,0,0,210,214,5,48,0,0,211,213,7,4,
  	0,0,212,211,1,0,0,0,213,216,1,0,0,0,214,212,1,0,0,0,214,215,1,0,0,0,215,
  	225,1,0,0,0,216,214,1,0,0,0,217,218,5,48,0,0,218,220,7,5,0,0,219,221,
  	7,6,0,0,220,219,1,0,0,0,221,222,1,0,0,0,222,220,1,0,0,0,222,223,1,0,0,
  	0,223,225,1,0,0,0,224,203,1,0,0,0,224,210,1,0,0,0,224,217,1,0,0,0,225,
  	70,1,0,0,0,226,229,3,73,36,0,227,229,3,77,38,0,228,226,1,0,0,0,228,227,
  	1,0,0,0,229,72,1,0,0,0,230,232,7,3,0,0,231,230,1,0,0,0,232,233,1,0,0,
  	0,233,234,1,0,0,0,233,231,1,0,0,0,234,235,1,0,0,0,235,237,5,46,0,0,236,
  	238,7,3,0,0,237,236,1,0,0,0,238,239,1,0,0,0,239,237,1,0,0,0,239,240,1,
  	0,0,0,240,248,1,0,0,0,241,243,7,3,0,0,242,241,1,0,0,0,243,244,1,0,0,0,
  	244,242,1,0,0,0,244,245,1,0,0,0,245,246,1,0,0,0,246,248,5,46,0,0,247,
  	231,1,0,0,0,247,242,1,0,0,0,248,250,1,0,0,0,249,251,3,75,37,0,250,249,
  	1,0,0,0,250,251,1,0,0,0,251,259,1,0,0,0,252,254,7,3,0,0,253,252,1,0,0,
  	0,254,255,1,0,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,257,1,0,0,0,257,
  	259,3,75,37,0,258,247,1,0,0,0,258,253,1,0,0,0,259,74,1,0,0,0,260,262,
  	7,7,0,0,261,263,7,8,0,0,262,261,1,0,0,0,262,263,1,0,0,0,263,265,1,0,0,
  	0,264,266,7,3,0,0,265,264,1,0,0,0,266,267,1,0,0,0,267,265,1,0,0,0,267,
  	268,1,0,0,0,268,76,1,0,0,0,269,270,5,48,0,0,270,288,7,5,0,0,271,273,7,
  	6,0,0,272,271,1,0,0,0,273,274,1,0,0,0,274,275,1,0,0,0,274,272,1,0,0,0,
  	275,276,1,0,0,0,276,278,5,46,0,0,277,279,7,6,0,0,278,277,1,0,0,0,279,
  	280,1,0,0,0,280,278,1,0,0,0,280,281,1,0,0,0,281,289,1,0,0,0,282,284,7,
  	6,0,0,283,282,1,0,0,0,284,285,1,0,0,0,285,283,1,0,0,0,285,286,1,0,0,0,
  	286,287,1,0,0,0,287,289,5,46,0,0,288,272,1,0,0,0,288,283,1,0,0,0,289,
  	291,1,0,0,0,290,292,3,79,39,0,291,290,1,0,0,0,291,292,1,0,0,0,292,302,
  	1,0,0,0,293,294,5,48,0,0,294,296,7,5,0,0,295,297,7,6,0,0,296,295,1,0,
  	0,0,297,298,1,0,0,0,298,296,1,0,0,0,298,299,1,0,0,0,299,300,1,0,0,0,300,
  	302,3,79,39,0,301,269,1,0,0,0,301,293,1,0,0,0,302,78,1,0,0,0,303,305,
  	7,9,0,0,304,306,7,8,0,0,305,304,1,0,0,0,305,306,1,0,0,0,306,308,1,0,0,
  	0,307,309,7,3,0,0,308,307,1,0,0,0,309,310,1,0,0,0,310,308,1,0,0,0,310,
  	311,1,0,0,0,311,80,1,0,0,0,312,313,5,47,0,0,313,314,5,42,0,0,314,318,
  	1,0,0,0,315,317,9,0,0,0,316,315,1,0,0,0,317,320,1,0,0,0,318,319,1,0,0,
  	0,318,316,1,0,0,0,319,321,1,0,0,0,320,318,1,0,0,0,321,322,5,42,0,0,322,
  	323,5,47,0,0,323,324,1,0,0,0,324,325,6,40,0,0,325,82,1,0,0,0,326,327,
  	5,47,0,0,327,328,5,47,0,0,328,332,1,0,0,0,329,331,8,10,0,0,330,329,1,
  	0,0,0,331,334,1,0,0,0,332,330,1,0,0,0,332,333,1,0,0,0,333,335,1,0,0,0,
  	334,332,1,0,0,0,335,336,6,41,0,0,336,84,1,0,0,0,337,339,7,11,0,0,338,
  	337,1,0,0,0,339,340,1,0,0,0,340,338,1,0,0,0,340,341,1,0,0,0,341,342,1,
  	0,0,0,342,343,6,42,0,0,343,86,1,0,0,0,28,0,200,207,214,222,224,228,233,
  	239,244,247,250,255,258,262,267,274,280,285,288,291,298,301,305,310,318,
  	332,340,1,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysy2022lexerLexerStaticData = staticData.release();
}

}

sysy2022Lexer::sysy2022Lexer(CharStream *input) : Lexer(input) {
  sysy2022Lexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *sysy2022lexerLexerStaticData->atn, sysy2022lexerLexerStaticData->decisionToDFA, sysy2022lexerLexerStaticData->sharedContextCache);
}

sysy2022Lexer::~sysy2022Lexer() {
  delete _interpreter;
}

std::string sysy2022Lexer::getGrammarFileName() const {
  return "sysy2022.g4";
}

const std::vector<std::string>& sysy2022Lexer::getRuleNames() const {
  return sysy2022lexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& sysy2022Lexer::getChannelNames() const {
  return sysy2022lexerLexerStaticData->channelNames;
}

const std::vector<std::string>& sysy2022Lexer::getModeNames() const {
  return sysy2022lexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& sysy2022Lexer::getVocabulary() const {
  return sysy2022lexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView sysy2022Lexer::getSerializedATN() const {
  return sysy2022lexerLexerStaticData->serializedATN;
}

const atn::ATN& sysy2022Lexer::getATN() const {
  return *sysy2022lexerLexerStaticData->atn;
}




void sysy2022Lexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sysy2022lexerLexerInitialize();
#else
  ::antlr4::internal::call_once(sysy2022lexerLexerOnceFlag, sysy2022lexerLexerInitialize);
#endif
}
