#pragma once
#include "Parser.h"
#include "../TestToken.h"

class TestParser : public Parser
{
public:
	TestParser(Tokens const& tokens);
};

