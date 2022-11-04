cmake_minimum_required(VERSION 3.24)

project(Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_HEADERS 
AbstractParser.h  SharedParser.h	  SqlParser.h	TestToken.h
CppParser.h	  SqlCreateDefinition.h   State.h	Token.h
Lexer.h		  SqlCreateTableParser.h  TestLexer.h
Parser.h	  SqlLexer.h		  TestParser.h
)

set(PROJECT_SOURCES 
AbstractParser.cpp  SharedParser.cpp	      SqlParser.cpp   Token.cpp
CppParser.cpp	    SqlCreateDefinition.cpp   State.cpp       main.cpp
Lexer.cpp	    SqlCreateTableParser.cpp  TestLexer.cpp
Parser.cpp	    SqlLexer.cpp	      TestParser.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
