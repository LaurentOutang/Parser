#pragma once
#include "../../include/Token.h"


template<StringLiteral str>
using PackId = Pack<TokenType::IDENTIFIER, str>;

template<StringLiteral str>
using PackPunc = Pack<TokenType::PUNCTUATOR, str>;

using CreateToken = PackId<"CREATE">;
using TableToken = PackId<"TABLE">;
using IfToken = PackId<"IF">;
using NotToken = PackId<"NOT">;
using ExistsToken = PackId<"EXISTS">;
using NullToken = PackId<"NULL">;
using DefaultToken = PackId<"DEFAULT">;
using PrimaryToken = PackId<"PRIMARY">;
using KeyToken = PackId<"KEY">;
using UniqueToken = PackId<"UNIQUE">;
using ConstraintToken = PackId<"CONSTRAINT">;
using LeftParToken = PackPunc<"(">;
using RightParToken = PackPunc<")">;
using SemiColonToken = PackPunc<";">;
using CommaToken = PackPunc<",">;


