#pragma once
#include "Parser.h"

class SqlCreateDefinitionParser : public Parser
{
public:
	SqlCreateDefinitionParser(Tokens const& tokens);
};

