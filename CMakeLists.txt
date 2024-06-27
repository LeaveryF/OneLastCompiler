
project(OneLastCompiler LANGUAGES CXX)

# TODO: ANTLR4 CodeGen Configuration

# glob all source files under src/ recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(main ${SOURCES})
target_include_directories(main PRIVATE include/)
