#pragma once
#include "../SqlTokens.h"
#include "../State.h"

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
struct acceptPublicIdentifier : public Acceptor
{
	acceptPublicIdentifier() : Acceptor([](Cursor const& cursor) {
        auto currentToken = cursor.head;
        StringCondition cond;
        if (currentToken->type == TokenType::IDENTIFIER && cond(currentToken->str))
        {
            Tokens::const_iterator next = cursor.head;
            ++next;
            return AcceptorResult{ .accepted = true, .next = next };
        }
        else return AcceptorResult{ .accepted = false, .next = cursor.head };
    }, 1)
	{

	}
};

struct IntegerAcceptor : public Acceptor
{
	IntegerAcceptor() : Acceptor([](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == TokenType::INTEGER)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return AcceptorResult{ .accepted = true, .next = next };
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	}, 1)
	{

	}
};

struct SqlAcceptor
{
    static inline acceptAny anyToken;

    static inline IntegerAcceptor integer;
    static inline acceptTokens<CommaToken> comma;
    static inline acceptTokens<UniqueToken> unique;
    static inline acceptTokens<DefaultToken> Default;
    static inline acceptTokens<LeftParToken> leftPar;
    static inline acceptTokens<RightParToken> rightPar;
    static inline acceptTokens<ConstraintToken> constraint;

    static inline acceptTokens<NotToken, NullToken> notNull;
    static inline acceptTokens<CreateToken, TableToken> createTable;
    static inline acceptTokens<PrimaryToken, KeyToken> primaryKey;
    static inline acceptTokens<IfToken, NotToken, ExistsToken> ifNotExists;
    static inline acceptTokens<RightParToken, SemiColonToken> rightParSemiColon;

    static inline acceptPublicIdentifier<isNotReserved> notReservedPublicIdentifier;
    static inline acceptPublicIdentifier<isSingleIdentifierTypes> publicSingleIdentifierType;
    static inline acceptPublicIdentifier<isSingleIdentifierSizedTypes> publicSingleIdentifierSizedType;

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