cmake_minimum_required(VERSION 3.16)
project(slr_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(FLEX REQUIRED)

FLEX_TARGET(Lexer
    ${CMAKE_SOURCE_DIR}/src/lexer.l
    ${CMAKE_BINARY_DIR}/lex_flex.cpp
    COMPILE_FLAGS "--c++"
)

add_executable(slr_parser
    src/main.cpp
    src/grammar.cpp
    src/lr0.cpp
    src/slr_table.cpp
    src/parser.cpp
    ${FLEX_Lexer_OUTPUTS}
)

add_executable(slr_tests
    tests/tests.cpp
    src/grammar.cpp
    src/lr0.cpp
    src/slr_table.cpp
    src/parser.cpp
    ${FLEX_Lexer_OUTPUTS}
)

target_include_directories(slr_parser PRIVATE
    include
    ${CMAKE_BINARY_DIR}
)

target_include_directories(slr_tests PRIVATE
    include
    ${CMAKE_BINARY_DIR}
)

add_test(NAME slr_tests COMMAND slr_tests)