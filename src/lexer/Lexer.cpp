#include "../../include/lexer/Lexer.h"

TokenResult operator|(TokenResult const& result1, TokenResult const& result2)
{
	return {
		.succeed = result1.succeed || result2.succeed,
		.token = result1.succeed ? result1.token : result2.token
	};
}

Lexer::Lexer(std::string_view code) : m_code(code)
{
}

TokenResult Lexer::readNumber()
{
	auto beg = m_code.cbegin();
	auto end = m_code.cend();
	bool floating = false;
	while (beg != end && isDigit(*beg) || !floating && *beg == '.')
	{
		if(floating == false)
			floating = *beg == '.';
		++beg;
	}

	return {
		.succeed = beg != m_code.cbegin(),
		.token = {
			.str = std::string_view(m_code.cbegin(), beg),
			.type = static_cast<size_t>(floating ? TokenType::FLOATING : TokenType::INTEGER)
		}
	};
}

TokenResult Lexer::readLiteral()
{
	auto beg = m_code.cbegin();
	bool quoteEnded = false;
	if (beg != m_code.cend() && *beg == '"')
	{
		++beg;
		bool escaped = false;
		while (beg != m_code.cend() && !quoteEnded)
		{
			if (*beg == '\\')
			{
				escaped = true;
				continue;
			}
			else if (*beg == '"' && !escaped)
				quoteEnded = true;
			escaped = false;
		}
	}
	return TokenResult{
		.succeed = quoteEnded == true,
		.token = {
			.str = std::string_view(m_code.cbegin(), beg),
			.type = TokenType::LITERAL
		}
	};
}

TokenResult Lexer::readNonNumericStartingIdenfitier()
{
	auto beg = m_code.cbegin();
	bool firstLetter = true;
	while (beg != m_code.cend() && (isLetter(*beg)  || isUnderscore(*beg) || isDigit(*beg) && !firstLetter))
	{
		firstLetter = false;
		++beg;
	}
	return {
		.succeed = beg != m_code.cbegin(),
		.token = {
			.str = std::string_view(m_code.cbegin(), beg),
			.type = TokenType::IDENTIFIER
		}
	};
}

TokenResult Lexer::readPunctuator()
{
	auto beg = m_code.cbegin();
	return {
		.succeed = beg != m_code.cend() && (*beg == ',' || *beg == '(' || *beg == ')' || *beg == ';'),
		.token = {
			.str = std::string_view(m_code.cbegin(), beg != m_code.cend() ? ++beg : m_code.cbegin()),
			.type = TokenType::PUNCTUATOR
		}
	};
}

TokenResult Lexer::readWhiteSpaces()
{
	auto beg = m_code.cbegin();
	while (beg != m_code.cend() && isWhiteSpace(*beg))
	{
		++beg;
	}
	return {
		.succeed = beg != m_code.cbegin(),
		.token = {
			.str = std::string_view(m_code.cbegin(), beg),
			.type = TokenType::WHITESPACE
		}
	};
}

bool Lexer::throwUnknownTokenError()
{
	throw UnknownTokenError();
}

bool Lexer::isLetter(char const c)
{
	return c >= 65 && c <= 90 || c >= 97 && c <= 122;
}

bool Lexer::isDigit(char const c)
{
	return c >= 48 && c <= 57;
}

bool Lexer::isAlphaNumeric(char const c)
{
	return isLetter(c) || isDigit(c);
}

bool Lexer::isUnderscore(char const c)
{
	return c == '_';
}

bool Lexer::isWhiteSpace(char const c)
{
	return c >= 9 && c <= 13 || c == ' ';
}
