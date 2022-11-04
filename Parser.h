#pragma once
#include "State.h"
#include "AbstractParser.h"
#include <memory>


class Parser : public AbstractParser
{
public:
	Parser(Tokens const& token);
	
	virtual AbtractSyntaxTree parse() final;
private:
	bool reachedEnd() const;
protected:
	std::vector<Cursor> m_cursors;
};

