#pragma once
#include "Token.h"

namespace test {
	enum TestTokenType { PUNCTUATOR = TokenType::WHITESPACE + 1, WHITESPACE, OPERATOR, UNKNOWN };
}

