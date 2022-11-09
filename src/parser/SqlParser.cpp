#include "../../include/parser/SqlParser.h"

SqlParser::SqlParser(Tokens const& tokens) : Parser(tokens), m_sqlCreateTableParser(tokens)
{
    m_init.addEpsilon(m_sqlCreateTableParser.getInit());
    m_sqlCreateTableParser.getEnd().addEpsilon(m_end);
}
