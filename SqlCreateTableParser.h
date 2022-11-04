#pragma once
#include "AbstractParser.h"

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

inline std::vector<std::string_view> single_identifier_types{
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

struct isSingleIdentifierTypes
{
    bool operator()(std::string_view const& str);
};

struct isDoubleIdentifierTypes
{
    bool operator()(std::string_view const& str);
};

struct isSingleIdentifierSizedTypes
{
    bool operator()(std::string_view const& str);
};

struct isSingleIdentifierDoubleSizedTypes
{
    bool operator()(std::string_view const& str);
};

struct isDoubleIdentifierSizedTypes
{
    bool operator()(std::string_view const& str);
};

struct isNotReserved
{
    bool operator()(std::string_view const& str);
};

template<typename StringCondition>
struct acceptPublicIdentifier
{

    acceptPublicIdentifier(Tokens::const_iterator end) : m_end(end) {}

    AcceptorResult operator()(Cursor const& cursor) {
        auto currentToken = cursor.head;
        StringCondition cond;
        if (currentToken != m_end && currentToken->type == TokenType::IDENTIFIER && cond(currentToken->str))
        {
            Tokens::const_iterator next = cursor.head;
            ++next;
            return AcceptorResult{ .accepted = true, .next = next };
        }
        else return AcceptorResult{ .accepted = false, .next = cursor.head };
    };
private:
    Tokens::const_iterator m_end;
};

using CreateToken = Pack<TokenType::IDENTIFIER, "CREATE">;
using TableToken = Pack<TokenType::IDENTIFIER, "TABLE">;
using IfToken = Pack<TokenType::IDENTIFIER, "IF">;
using NotToken = Pack<TokenType::IDENTIFIER, "NOT">;
using ExistsToken = Pack<TokenType::IDENTIFIER, "EXISTS">;
using NullToken = Pack<TokenType::IDENTIFIER, "NULL">;
using DefaultToken = Pack<TokenType::IDENTIFIER, "DEFAULT">;
using PrimaryToken = Pack<TokenType::IDENTIFIER, "PRIMARY">;
using KeyToken = Pack<TokenType::IDENTIFIER, "KEY">;
using UniqueToken = Pack<TokenType::IDENTIFIER, "UNIQUE">;
using ConstraintToken = Pack<TokenType::IDENTIFIER, "CONSTRAINT">;
using LeftParToken = Pack<TokenType::PUNCTUATOR, "(">;
using RightParToken = Pack<TokenType::PUNCTUATOR, ")">;
using SemiColonToken = Pack<TokenType::PUNCTUATOR, ";">;
using CommaToken = Pack<TokenType::PUNCTUATOR, ",">;

class SqlCreateTableParser : public AbstractParser
{
public:
	SqlCreateTableParser(Tokens const& tokens);

    std::string_view getCurrentType() const { return m_type; }
protected:
    std::string_view m_type;
};


struct DefaultValueAcceptator
{
    DefaultValueAcceptator(Tokens::const_iterator end, SqlCreateTableParser* parser) : m_end(end), m_parser(parser)
    {
    }

    AcceptorResult operator()(Cursor const& cursor) {
        auto currentToken = cursor.head;

        if (currentToken != m_end && m_parser)
        {
            std::string_view type = m_parser->getCurrentType();
            if (currentToken->type == TokenType::IDENTIFIER)
            {
                if (currentToken->str == "NULL")
                {
                    Tokens::const_iterator next = cursor.head;
                    ++next;
                    return AcceptorResult{ .accepted = true, .next = next };
                }
                else if (type == "BOOLEAN" && (currentToken->str == "TRUE" || currentToken->str == "FALSE")
                    || type == "TIMESTAMP" && currentToken->str == "CURRENT_TIMESTAMP"
                    || type == "DATE" && currentToken->str == "CURRENT_DATE"
                    || type == "TIME" && currentToken->str == "CURRENT_TIME")
                {
                    Tokens::const_iterator next = cursor.head;
                    ++next;
                    return AcceptorResult{ .accepted = true, .next = next };
                }
            }
            else if (currentToken->type == TokenType::INTEGER)
            {
                if (type == "INTEGER" ||
                    type == "SMALLINT" ||
                    type == "BIGINT" ||
                    type == "SMALLSERIAL" ||
                    type == "SERIAL" ||
                    type == "BIGSERIAL")
                {
                    Tokens::const_iterator next = cursor.head;
                    ++next;
                    return AcceptorResult{ .accepted = true, .next = next };
                }
            }
            else if (currentToken->type == TokenType::FLOATING)
            {
                if (type == "DECIMAL" ||
                    type == "NUMERIC" ||
                    type == "REAL")
                {
                    Tokens::const_iterator next = cursor.head;
                    ++next;
                    return AcceptorResult{ .accepted = true, .next = next };
                }
            }
            else if (currentToken->type == TokenType::LITERAL)
            {
                if (type == "TEXT" ||
                    type == "VARCHAR")
                {
                    Tokens::const_iterator next = cursor.head;
                    ++next;
                    return AcceptorResult{ .accepted = true, .next = next };
                }
            }
        }
        return AcceptorResult{ .accepted = false, .next = cursor.head };
    };
private:
    SqlCreateTableParser* m_parser = nullptr;
    Tokens::const_iterator m_end;
};
