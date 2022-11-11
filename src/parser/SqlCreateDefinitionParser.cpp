#include "../../include/parser/SqlCreateDefinitionParser.h"
#include "../../include/SqlTokens.h"
#include "../../include/acceptor/SqlAcceptor.h"
#include <vector>

inline std::vector<std::string_view> reserved_keywords{
    "CREATE",
    "TABLE",
    "IF",
    "NOT",
    "EXIST",
    "DEFAULT",
    "NULL",
    "TRUE",
    "FALSE",
    "CURRENT_TIMESTAMP",
    "INT",
    "INTEGER",
    "BIGINT",
    "SMALLINT",
    "SERIAL",
    "VARCHAR",
    "CHAR",
    "BOOLEAN",
    "BOOL",
    "DATE",
    "DATETIME",
    "BYTEA"
};



inline std::vector<std::string_view> double_identifier_types{
    "double precision"
};

inline std::vector<std::string_view> single_identifier_sized_types{
    "bit",
    "character",
    "varbit",
    "char",
    "varchar"
};

inline std::vector<std::string_view> single_identifier_double_sized_types{
    "numeric",
    "decimal"
};

inline std::vector<std::string_view> double_identifier_sized_types{
    "bit varying",
    "character varying"
};

inline std::vector<std::string_view> with_time_zone_types{
    "time",
    "timestamp"
};

inline std::vector<std::string_view> interval_type{
    "interval"
};


SqlCreateDefinitionParser::SqlCreateDefinitionParser(Tokens const& tokens) : Parser(tokens)
{

    State& s5 = newState();
    State& s6 = newState();
    State& s7 = newState();
    State& s8 = newState();
    State& s9 = newState();
    State& s10 = newState();
    State& s11 = newState();

    m_init.add(SqlAcceptor::notReservedPublicIdentifier, s5);

    //Type
    s5.add(SqlAcceptor::publicSingleIdentifierType, s6);

    //Type(Number)
    /* s5.add(1, acceptPublicSingleIdentifierSizedType, s7);
    s7.add(1, acceptLeftPar, s8);
    s8.add(1, acceptInteger, s9);
    s9.add(1, acceptRightPar, s6); */


    s6.add(SqlAcceptor::notNull, s10);
    s6.addEpsilon(s10);
    s10.add(SqlAcceptor::Default, s11);
    s10.addEpsilon(m_end);
    s11.add(SqlAcceptor::anyToken, m_end);
    //s11.add(DefaultValueAcceptator(tokens.cend(), this), m_end);
}
