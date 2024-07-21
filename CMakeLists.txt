
project(OneLastCompiler LANGUAGES CXX)

cmake_minimum_required(VERSION 3.20)

# ANTLR4 Configuration
##########################################################################
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 17
set(CMAKE_CXX_STANDARD 17)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)

# Specify the version of the antlr4 library needed for this project.
# By default the latest version of antlr4 will be used.  You can specify a
# specific, stable version by setting a repository tag value or a link
# to a zip file containing the libary source.
# set(ANTLR4_TAG 4.13.1)
# set(ANTLR4_ZIP_REPOSITORY https://github.com/antlr/antlr4/archive/refs/tags/4.13.1.zip)

# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
# set(ANTLR_EXECUTABLE /home/user/antlr-4.13.1-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
# find_package(ANTLR REQUIRED)

# Call macro to add lexer and grammar to your build dependencies.
# antlr_target(SampleGrammarLexer TLexer.g4 LEXER
#              PACKAGE antlrcpptest)
# antlr_target(SampleGrammarParser TParser.g4 PARSER
#              PACKAGE antlrcpptest
#              DEPENDS_ANTLR SampleGrammarLexer
#              COMPILE_FLAGS -lib ${ANTLR_SampleGrammarLexer_OUTPUT_DIR})

# include generated files in project environment
# include_directories(${ANTLR_SampleGrammarLexer_OUTPUT_DIR})
# include_directories(${ANTLR_SampleGrammarParser_OUTPUT_DIR})

# add generated grammar to demo binary target
# add_executable(demo main.cpp
#                ${ANTLR_SampleGrammarLexer_CXX_OUTPUTS}
#                ${ANTLR_SampleGrammarParser_CXX_OUTPUTS})
# target_link_libraries(demo antlr4_static)
##########################################################################

# glob all source files under src/ recursively
file(GLOB_RECURSE SOURCES "src/*.cpp" "antlr/*.cpp")

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE include/ antlr/)
target_link_libraries(main antlr4_shared)
add_custom_command(TARGET main
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                           -E copy ${ANTLR4_RUNTIME_LIBRARIES} .
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# test targets
file(GLOB_RECURSE LIB_IR_SOURCES "src/ir/*.cpp")
add_executable(test_ir_asm test/test_ir_asm.cpp ${LIB_IR_SOURCES})
target_include_directories(test_ir_asm PRIVATE include/ antlr/)
target_link_libraries(test_ir_asm antlr4_shared)

# test targets
file(GLOB_RECURSE LIB_SYMTAB_SOURCES "src/utils/symtab.cpp")
add_executable(test_symtab test/test_symtab.cpp ${LIB_SYMTAB_SOURCES})
target_include_directories(test_symtab PRIVATE include/ antlr/)
target_link_libraries(test_symtab antlr4_shared)
