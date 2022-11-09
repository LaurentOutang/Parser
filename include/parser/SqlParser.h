#pragma once
#include "SqlCreateTableParser.h"
#include "Parser.h"



class SqlParser : public Parser//If more consider put this as member
{
public:
	SqlParser(Tokens const& tokens);
protected:
    SqlCreateTableParser m_sqlCreateTableParser;
};
