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
    connect("init", "free_identifier", SqlAcceptor::freeIdentifier);

//Types
    connect("free_identifier", "integer_type", SqlAcceptor::integerType);
    connect("free_identifier", "apn_type", SqlAcceptor::arbitraryPrecisionNumberType);
    connect("free_identifier", "floating_point_type", SqlAcceptor::floatingPointType);
    connect("free_identifier", "floating_point_type", SqlAcceptor::floatingPointType2);
    connect("free_identifier", "serial_type", SqlAcceptor::serialType);

//Read int line
    connect("integer_type", "not_null_int", SqlAcceptor::notNull);
    connect("integer_type", "not_null_int");
    connect("not_null_int", "default_int", SqlAcceptor::Default);    
    connect("not_null_int", "end");
    connect("default_int", "end", SqlAcceptor::integer);

//Read numeric line
    connect("apn_type", "(_apn", SqlAcceptor::leftPar);
    connect("apn_type", "end");
    connect("(_apn", "integer1_apn", SqlAcceptor::integer);    
    connect("integer1_apn", ",_apn", SqlAcceptor::comma);
    connect("integer1_apn", "right_par_apn");
    connect(",_apn", "integer2_apn", SqlAcceptor::integer);
    connect("integer2_apn", "right_par_apn", SqlAcceptor::rightPar);
    connect("right_par_apn", "not_null_apn", SqlAcceptor::notNull);
    connect("right_par_apn", "not_null_apn");
    connect("not_null_apn", "default_apn", SqlAcceptor::Default);
    connect("not_null_apn", "end");
    connect("default_apn", "end", SqlAcceptor::arbitraryPrecisionNumber);

//Read floating point line

    connect("floating_point_type", "not_null_fp", SqlAcceptor::notNull);
    connect("floating_point_type", "not_null_fp");
    connect("not_null_fp", "default_fp", SqlAcceptor::Default);
    connect("not_null_fp", "end");
    connect("default_fp", "end", SqlAcceptor::floatingPoint);

//Read serial line
    connect("serial_type", "integer_type");
    connect("serial_type", "end");
}
