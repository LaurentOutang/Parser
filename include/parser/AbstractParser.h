#pragma once
#include "../State.h"

class ParseError {};

class ReachFinalState {};

class EndParseTokensInInvalidStates {};

class AbtractSyntaxTree {};

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

class AbstractParser
{
public:
	AbstractParser(Tokens const& token);	

	State& getInit() const { return m_init; }
	State& getEnd() const { return m_end; }
protected:
	State& newState();
	Tokens const& m_tokens;
private:	
	std::vector<std::shared_ptr<State>> m_states;
protected:
	State& m_init;
	State& m_end;
private:
	State * m_head = &m_init;
};

