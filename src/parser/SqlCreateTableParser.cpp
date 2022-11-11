#include "../../include/parser/SqlCreateTableParser.h"
#include "../../include/SqlAcceptor.h"

SqlCreateTableParser::SqlCreateTableParser(Tokens const& tokens) : 
    AbstractParser(tokens),
    m_createDefinitionParser(tokens)
{
    State& s1 = newState();
    State& s2 = newState();
    State& s3 = newState();
    State& parAfterCreateTable = newState();
    
    State& s12 = newState();
    State& s13 = newState();

    m_init.add(2, SqlAcceptor::createTable, s1);
    s1.add(1, SqlAcceptor::notReservedPublicIdentifier, s2);
    s2.add(3, SqlAcceptor::ifNotExists, s3);
    s2.addEpsilon(s3);
    s3.add(1, SqlAcceptor::leftPar, parAfterCreateTable);

    parAfterCreateTable.addEpsilon(m_createDefinitionParser.getInit());
    m_createDefinitionParser.getEnd().addEpsilon(s12);

    s12.add(1, SqlAcceptor::comma, parAfterCreateTable);
    s12.add(2, SqlAcceptor::rightParSemiColon, s13);
    s13.addEpsilon(m_init);
    s13.addEpsilon(m_end);
}
