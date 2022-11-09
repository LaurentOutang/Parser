#pragma once
#include "SqlCreateDefinitionParser.h"

class SqlCreateTableParser : public AbstractParser
{
public:
	SqlCreateTableParser(Tokens const& tokens);

    std::string_view getCurrentType() const { return m_type; }
protected:
    std::string_view m_type;
    SqlCreateDefinitionParser m_createDefinitionParser;
};