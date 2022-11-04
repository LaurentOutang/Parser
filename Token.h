#pragma once
#include <vector>
#include <string_view>

enum TokenType : size_t { INTEGER, FLOATING, LITERAL, PUNCTUATOR, IDENTIFIER, WHITESPACE };

struct Token
{
	std::string_view str;
	size_t type;
};

using Tokens = std::vector<Token>;
