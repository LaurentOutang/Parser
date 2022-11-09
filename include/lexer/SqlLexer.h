#pragma once
#include "Lexer.h"

class SqlLexer : public Lexer
{
public:
	SqlLexer(std::string_view const& code);
	Tokens tokenize() override;
private:
	TokenResult readToken();
};

