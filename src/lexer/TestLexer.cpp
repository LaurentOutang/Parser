#include "../../include/lexer/TestLexer.h"
#include "../../include/TestToken.h"

TestLexer::TestLexer(std::string_view code) : Lexer(code)
{

}

Tokens TestLexer::tokenize()
{
	Tokens tokens;

	Token token;
	while (readToken(token))
	{
		tokens.push_back(token);
	}

	return tokens;
}

bool TestLexer::readToken(Token& token)
{
	try
	{
		return readSingleCharToken(token) || TestLexer::throwUnknownTokenError();
	}
	catch (EndOfFile const&)
	{
		return false;
	}
}

bool TestLexer::readSingleCharToken(Token& token)
{
	std::string_view::const_iterator currentChar = m_code.begin();
	if(currentChar == m_code.end())
		throw EndOfFile();
	char const& c = *currentChar;
	if (c == '(' || c == ')')
	{
		token.type = test::TestTokenType::PUNCTUATOR;
		token.str = m_code.substr(0, 1);
		m_code.remove_prefix(1);
		return true;
	}
	else if (c == ' ' || c <= 13 && c >= 9)
	{
		token.type = test::TestTokenType::WHITESPACE;
		token.str = m_code.substr(0, 1);
		m_code.remove_prefix(1);
		return true;
	}
	else if (c == '*')
	{
		token.type = test::TestTokenType::OPERATOR;
		token.str = m_code.substr(0, 1);
		m_code.remove_prefix(1);
		return true;
	}
	return false;
}


