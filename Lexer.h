#pragma once
#include "Token.h"
#include <string_view>

class UnknownTokenError
{

};

class EndOfFile
{

};

struct TokenResult
{
	bool succeed = false;
	Token token;
	operator bool() { return succeed; }
};

TokenResult operator|(TokenResult const& result1, TokenResult const& result2);

class Lexer
{
public:
	Lexer(std::string_view code);
	virtual Tokens tokenize() = 0;
protected:
	TokenResult readNumber();
	TokenResult readLiteral();
	TokenResult readNonNumericStartingIdenfitier();
	TokenResult readPunctuator();
	TokenResult readWhiteSpaces();
	static bool throwUnknownTokenError();
	static bool isLetter(char const c);
	static bool isDigit(char const c);
	static bool isAlphaNumeric(char const c);
	static bool isUnderscore(char const c);
	static bool isWhiteSpace(char const c);
	static inline const TokenResult EndTokenResult = {
		.succeed = false,
		.token = std::string_view()
	};
protected:
	std::string_view m_code;
};

