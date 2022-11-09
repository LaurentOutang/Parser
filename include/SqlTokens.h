#pragma once
#include "../../include/Token.h"

using CreateToken = Pack<TokenType::IDENTIFIER, "CREATE">;
using TableToken = Pack<TokenType::IDENTIFIER, "TABLE">;
using IfToken = Pack<TokenType::IDENTIFIER, "IF">;
using NotToken = Pack<TokenType::IDENTIFIER, "NOT">;
using ExistsToken = Pack<TokenType::IDENTIFIER, "EXISTS">;
using NullToken = Pack<TokenType::IDENTIFIER, "NULL">;
using DefaultToken = Pack<TokenType::IDENTIFIER, "DEFAULT">;
using PrimaryToken = Pack<TokenType::IDENTIFIER, "PRIMARY">;
using KeyToken = Pack<TokenType::IDENTIFIER, "KEY">;
using UniqueToken = Pack<TokenType::IDENTIFIER, "UNIQUE">;
using ConstraintToken = Pack<TokenType::IDENTIFIER, "CONSTRAINT">;
using LeftParToken = Pack<TokenType::PUNCTUATOR, "(">;
using RightParToken = Pack<TokenType::PUNCTUATOR, ")">;
using SemiColonToken = Pack<TokenType::PUNCTUATOR, ";">;
using CommaToken = Pack<TokenType::PUNCTUATOR, ",">;


