cmake_minimum_required(VERSION 3.16)
project(slr_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(slr_parser
    src/main.cpp
    src/lexer.cpp
    src/grammar.cpp
    src/lr0.cpp
    src/slr_table.cpp
    src/parser.cpp
)

target_include_directories(slr_parser PRIVATE include)
