#include "../../include/parser/SqlCreateDefinitionParser.h"
#include "../../include/SqlTokens.h"
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


/* struct DefaultValueAcceptator
{
    DefaultValueAcceptator(Tokens::const_iterator end, SqlCreateDefinitionParser* parser) : m_end(end), m_parser(parser)
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
    SqlCreateDefinitionParser* m_parser = nullptr;
    Tokens::const_iterator m_end;
}; */


SqlCreateDefinitionParser::SqlCreateDefinitionParser(Tokens const& tokens) : Parser(tokens)
{
    auto acceptCreateTable = acceptTokens<CreateToken, TableToken>();
    auto acceptNotReservedPublicIdentifier = acceptPublicIdentifier<isNotReserved>();
    auto acceptIfNotExists = acceptTokens<IfToken, NotToken, ExistsToken>();
    auto acceptNotNull = acceptTokens<NotToken, NullToken>();
    auto acceptDefault = acceptTokens<DefaultToken>();
    auto acceptLeftPar = acceptTokens<LeftParToken>();
    auto acceptRightPar = acceptTokens<RightParToken>();
    auto acceptPrimaryKey = acceptTokens<PrimaryToken, KeyToken>();
    auto acceptUnique = acceptTokens<UniqueToken>();
    auto acceptConstraint = acceptTokens<ConstraintToken>();
    auto acceptRightParSemiColon = acceptTokens<RightParToken, SemiColonToken>();
    auto acceptPublicSingleIdentifierType = acceptPublicIdentifier<isSingleIdentifierTypes>();
    auto acceptPublicSingleIdentifierSizedType = acceptPublicIdentifier<isSingleIdentifierSizedTypes>();
    auto acceptInteger = IntegerAcceptor();
    auto acceptComma = acceptTokens<CommaToken>();
    auto acceptAnyToken = acceptAny();

    State& s5 = newState();
    State& s6 = newState();
    State& s7 = newState();
    State& s8 = newState();
    State& s9 = newState();
    State& s10 = newState();
    State& s11 = newState();

    m_init.add(1, acceptNotReservedPublicIdentifier, s5);

    //Type
    s5.add(1, acceptPublicSingleIdentifierType, s6);

    //Type(Number)
    /* s5.add(1, acceptPublicSingleIdentifierSizedType, s7);
    s7.add(1, acceptLeftPar, s8);
    s8.add(1, acceptInteger, s9);
    s9.add(1, acceptRightPar, s6); */


    s6.add(2, acceptNotNull, s10);
    s6.addEpsilon(s10);
    s10.add(1, acceptDefault, s11);
    s10.addEpsilon(m_end);
    s11.add(1, acceptAnyToken, m_end);
    //s11.add(DefaultValueAcceptator(tokens.cend(), this), m_end);
}
