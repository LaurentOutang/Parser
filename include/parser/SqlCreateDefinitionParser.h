#pragma once
#include "Parser.h"


class SqlCreateDefinitionParser : public Parser
{
public:
	SqlCreateDefinitionParser(Tokens const& tokens);
private:
	static inline std::vector<std::string_view> single_identifier_types{
		"BIGINT",
		"BOOLEAN",
		"BOX",
		"BYTEA",
		"CIDR",
		"CIRCLE",
		"DATE",
		"INET",
		"INTEGER",
		"JSON",
		"JSONB",
		"LINE",
		"LSEG",
		"MACADDR",
		"MONEY",
		"PATH",
		"PG_LSN",
		"POINT",
		"POLYGON",
		"REAL",
		"SMALLINT",
		"SMALLSERIAL",
		"SERIAL",
		"TEXT",
		"TSQUERY",
		"TSVECTOR",
		"TXID_SNAPSHOT",
		"UUID",
		"XML",
		"INT8",
		"SERIAL8",
		"BOOL",
		"FLOAT8",
		"INT",
		"INT4",
		"FLOAT4",
		"INT2",
		"SERIAL2",
		"SERIAL4",
		"BIGSERIAL",
		"TIMETZ",
		"TIMESTAMPTZ",
		"VARCHAR"
	};
};

