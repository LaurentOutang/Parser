#pragma once
#include "Parser.h"



struct isSingleIdentifierTypes
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

struct isDoubleIdentifierTypes
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

struct isSingleIdentifierSizedTypes
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

struct isSingleIdentifierDoubleSizedTypes
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

struct isDoubleIdentifierSizedTypes
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

struct isNotReserved
{
    bool operator()(std::string_view const& str)
	{
		return true;
	}
};

template<typename StringCondition>
struct acceptPublicIdentifier
{
    AcceptorResult operator()(Cursor const& cursor) {
        auto currentToken = cursor.head;
        StringCondition cond;
        if (currentToken->type == TokenType::IDENTIFIER && cond(currentToken->str))
        {
            Tokens::const_iterator next = cursor.head;
            ++next;
            return AcceptorResult{ .accepted = true, .next = next };
        }
        else return AcceptorResult{ .accepted = false, .next = cursor.head };
    };
};

struct acceptAny
{
    AcceptorResult operator()(Cursor const& cursor) {
        auto currentToken = cursor.head;
		Tokens::const_iterator next = cursor.head;
		++next;
		return AcceptorResult{ .accepted = true, .next = next };
    };
};

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

