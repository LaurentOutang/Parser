#ifndef __SQLACCEPTOR__
#define __SQLACCEPTOR__
#include "../State.h"
#include "../SqlTokens.h"


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

template<typename pack, typename ... packs>
struct acceptTokens
{
	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == pack::type && currentToken->str == pack::str)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return acceptTokens<packs...>()(Cursor(cursor.state, next));
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	}
};

template<typename pack>
struct acceptTokens<pack>
{
	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == pack::type && currentToken->str == pack::str)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return AcceptorResult{ .accepted = true, .next = next };
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	};
};

struct IntegerAcceptor
{
	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == TokenType::INTEGER)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return AcceptorResult{ .accepted = true, .next = next };
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	};
};

struct SqlAcceptor
{
    static acceptAny anyToken;

    static IntegerAcceptor integer;
    static acceptTokens<CommaToken> comma;
    static acceptTokens<UniqueToken> unique;
    static acceptTokens<DefaultToken> Default;
    static acceptTokens<LeftParToken> leftPar;
    static acceptTokens<RightParToken> rightPar;
    static acceptTokens<ConstraintToken> constraint;

    static acceptTokens<NotToken, NullToken> notNull;
    static acceptTokens<CreateToken, TableToken> createTable;
    static acceptTokens<PrimaryToken, KeyToken> primaryKey;
    static acceptTokens<IfToken, NotToken, ExistsToken> ifNotExists;
    static acceptTokens<IfToken, NotToken, ExistsToken> ifNotExists;
    static acceptTokens<RightParToken, SemiColonToken> rightParSemiColon;

    static acceptPublicIdentifier<isNotReserved> notReservedPublicIdentifier;
    static acceptPublicIdentifier<isSingleIdentifierTypes> publicSingleIdentifierType;
    static acceptPublicIdentifier<isSingleIdentifierSizedTypes> publicSingleIdentifierSizedType;
};

#endif