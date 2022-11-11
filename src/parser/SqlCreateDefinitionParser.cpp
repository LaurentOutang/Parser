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
    State& s12 = newState();
    State& s13 = newState();
    State& s14 = newState();
    State& s15 = newState();
    State& s16 = newState();
    State& s17 = newState();
    State& s18 = newState();
    State& s19 = newState();
    State& s20 = newState();
    State& s21 = newState();
    State& s22 = newState();
    State& s23 = newState();
    State& s24 = newState();
    State& s25 = newState();
    State& s26 = newState();
    State& s27 = newState();
    State& s28 = newState();

    m_init.add(SqlAcceptor::freeIdentifier, s5);

//Type
    s5.add(SqlAcceptor::integerType, s6);
    s5.add(SqlAcceptor::arbitraryPrecisionNumberType, s7);
    s5.add(SqlAcceptor::floatingPointType, s8);
    s5.add(SqlAcceptor::floatingPointType2, s8);
    s5.add(SqlAcceptor::serialType, s9);

//Read int line
    s6.add(SqlAcceptor::notNull, s10);
    s6.addEpsilon(m_end);
    s10.add(SqlAcceptor::Default, s11);
    s11.add(SqlAcceptor::integer, m_end);
    s10.addEpsilon(m_end);

//Read numeric line
    s7.addEpsilon(s16);
    s7.add(SqlAcceptor::leftPar, s12);
    s12.add(SqlAcceptor::integer, s13);
    s13.add(SqlAcceptor::comma, s14);
    s13.addEpsilon(s15);
    s14.add(SqlAcceptor::integer, s15);
    s15.add(SqlAcceptor::rightPar, s16);
    s16.add(SqlAcceptor::notNull, s17);
    s16.addEpsilon(m_end);
    s17.add(SqlAcceptor::Default, s18);
    s18.add(SqlAcceptor::arbitraryPrecisionNumber, m_end);
    s17.addEpsilon(m_end);

//Floating point
    s8.add(SqlAcceptor::notNull, s19);
    s8.addEpsilon(m_end);
    s19.add(SqlAcceptor::Default, s20);
    s20.add(SqlAcceptor::floatingPoint, m_end);
    s19.addEpsilon(m_end);

//Serial
    s9.addEpsilon(s10);//Same as int
    s9.addEpsilon(m_end);
}
