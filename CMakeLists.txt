cmake_minimum_required(VERSION 3.5)

project(Parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIRECTORY ./src)
set(PARSER_SRC_DIR "${SOURCE_DIRECTORY}/parser")
set(LEXER_SRC_DIR "${SOURCE_DIRECTORY}/lexer")

set(HEADER_DIRECTORY ./include)
set(PARSER_HEADER_DIR "${HEADER_DIRECTORY}/parser")
set(LEXER_HEADER_DIR "${HEADER_DIRECTORY}/lexer")

include_directories(${PARSER_HEADER_DIR})
include_directories(${LEXER_HEADER_DIR})
include_directories(${PARSER_SRC_DIR})
include_directories(${LEXER_SRC_DIR})


set(PROJECT_HEADERS 
${PARSER_HEADER_DIR}/AbstractParser.h               ${PARSER_HEADER_DIR}/SharedParser.h	            ${PARSER_HEADER_DIR}/SqlParser.h	${HEADER_DIRECTORY}/TestToken.h
${PARSER_HEADER_DIR}/SqlCreateDefinitionParser.h    ${HEADER_DIRECTORY}/State.h	                    ${HEADER_DIRECTORY}/Token.h
${LEXER_HEADER_DIR}/Lexer.h		                    ${PARSER_HEADER_DIR}/SqlCreateTableParser.h     ${LEXER_HEADER_DIR}/TestLexer.h
${PARSER_HEADER_DIR}/Parser.h	                    ${LEXER_HEADER_DIR}/SqlLexer.h		            ${PARSER_HEADER_DIR}/TestParser.h
)

set(PROJECT_SOURCES 
${PARSER_SRC_DIR}/AbstractParser.cpp                ${PARSER_SRC_DIR}/SharedParser.cpp	        ${PARSER_SRC_DIR}/SqlParser.cpp   ${SOURCE_DIRECTORY}/Token.cpp
${PARSER_SRC_DIR}/SqlCreateDefinitionParser.cpp     ${SOURCE_DIRECTORY}/State.cpp               ${SOURCE_DIRECTORY}/main.cpp
${LEXER_SRC_DIR}/Lexer.cpp	                        ${PARSER_SRC_DIR}/SqlCreateTableParser.cpp  ${LEXER_SRC_DIR}/TestLexer.cpp
${PARSER_SRC_DIR}/Parser.cpp	                    ${LEXER_SRC_DIR}/SqlLexer.cpp	            ${PARSER_SRC_DIR}/TestParser.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
