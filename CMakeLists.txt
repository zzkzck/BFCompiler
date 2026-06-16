cmake_minimum_required(VERSION 3.20)

project(BFCompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BF
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/generation.cpp
)
