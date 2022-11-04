#pragma once
#include "Lexer.h"



class TestLexer : public Lexer
{
public:
	TestLexer(std::string_view code);
	Tokens tokenize() override;
private:
	bool readToken(Token& token);
	bool readSingleCharToken(Token& token);
};

