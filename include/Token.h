#pragma once
#include <vector>
#include <string_view>

enum TokenType : size_t { INTEGER, FLOATING, LITERAL, PUNCTUATOR, IDENTIFIER, WHITESPACE };

template<size_t N>
struct StringLiteral {
	constexpr StringLiteral(const char(&str)[N]) {
		std::copy_n(str, N, value);
	}
	char value[N];
};

template<size_t _type, StringLiteral _literal>
struct Pack
{
	static constexpr size_t type = _type;
	static constexpr auto str = _literal.value;
};

struct Token
{
	std::string_view str;
	size_t type;
};

using Tokens = std::vector<Token>;
