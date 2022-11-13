#include "../../include/parser/SqlCreateTableParser.h"
#include "../../include/acceptor/SqlAcceptor.h"

SqlCreateTableParser::SqlCreateTableParser(Tokens const& tokens) : 
    AbstractParser(tokens),
    m_createDefinitionParser(tokens)
{
    connect("init", "create_table", SqlAcceptor::createTable);
    connect("create_table", "table_name", SqlAcceptor::freeIdentifier);
    connect("table_name", "if_not_exists", SqlAcceptor::ifNotExists);
    connect("table_name", "if_not_exists");
    connect("if_not_exists", "left_par_create_table", SqlAcceptor::leftPar);
    connect("left_par_create_table", "create_definition", m_createDefinitionParser);
    connect("create_definition", "comma_create_definition", SqlAcceptor::comma);
    connect("create_definition", "right_par_semi_colon", SqlAcceptor::rightParSemiColon);
    connect("comma_create_definition", "left_par_create_table");
    connect("right_par_semi_colon", "init");
    connect("right_par_semi_colon", "end");
}
