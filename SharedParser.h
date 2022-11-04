#pragma once
#include "Parser.h"

class SharedParser : public AbstractParser
{
public:
	SharedParser(Tokens const& token);
	void bind(AbstractParser const& parser);
};

