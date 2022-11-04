#pragma once
#include "State.h"

class ParseError {};

class ReachFinalState {};

class EndParseTokensInInvalidStates {};

class AbtractSyntaxTree {};

template<size_t N>
struct StringLiteral {
	constexpr StringLiteral(const char(&str)[N]) {
		std::copy_n(str, N, value);
	}
	char value[N];
};

template<size_t type, StringLiteral _literal>
struct Pack
{
	static constexpr size_t type = type;
	static constexpr auto str = _literal.value;
};

template<typename pack, typename ... packs>
struct acceptTokens
{
	acceptTokens(Tokens::const_iterator end) : m_end(end) {}

	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken != m_end && currentToken->type == pack::type && currentToken->str == pack::str)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return acceptTokens<packs...>{m_end}(Cursor(cursor.state, next));
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	}
private:
	Tokens::const_iterator m_end;
};

template<typename pack>
struct acceptTokens<pack>
{
	acceptTokens(Tokens::const_iterator end) : m_end(end) {}

	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken != m_end && currentToken->type == pack::type && currentToken->str == pack::str)
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

struct IntegerAcceptor
{
	IntegerAcceptor(Tokens::const_iterator end) : m_end(end) {}

	AcceptorResult operator()(Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken != m_end && currentToken->type == TokenType::INTEGER)
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

class AbstractParser
{
public:
	AbstractParser(Tokens const& token);	

	State& getInit() const { return m_init; }
	State& getEnd() const { return m_end; }

	AbstractParser& then(Acceptor acceptor, Action&& action = Action(), bool advance = true);

protected:
	State& newState();

	Tokens const& m_tokens;
	State& m_init;
	State& m_end;
private:
	std::vector<std::unique_ptr<State>> m_states;
	State * m_head = &m_init;
};

