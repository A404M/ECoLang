cmake_minimum_required(VERSION 3.19)
project(ECoLang)

set(CMAKE_CXX_STANDARD 20)

add_executable(ECoLang main.cpp Compiler/Lexer.cpp Compiler/Lexer.h Compiler/Parser.cpp Compiler/Parser.h Classes/Numberical/Int.cpp Classes/Numberical/Int.h Classes/Numberical/Double.cpp Classes/Numberical/Double.h Classes/String/String.cpp Classes/String/String.h)