#include "SqlLexer.h"

SqlLexer::SqlLexer(std::string_view const& code) : Lexer(code)
{
}

Tokens SqlLexer::tokenize()
{
	Tokens tokens;

	TokenResult result;
	while (m_code.size() > 0 && (result = readToken()))
	{
		m_code.remove_prefix(result.token.str.size());
		if(result.token.type != TokenType::WHITESPACE)
			tokens.push_back(result.token);
	}

	return tokens;
}

TokenResult SqlLexer::readToken()
{
	return Lexer::readNumber() | 
		Lexer::readLiteral() | 
		Lexer::readNonNumericStartingIdenfitier() | 
		Lexer::readPunctuator() |
		Lexer::readWhiteSpaces() |
		EndTokenResult;
}
