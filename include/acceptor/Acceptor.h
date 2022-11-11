#pragma once
#include <functional>
#include "../Token.h"
#include "../Cursor.h"

struct AcceptorResult
{
	bool accepted;
	Tokens::const_iterator next;
};

using AcceptorFunc = std::function<AcceptorResult(Cursor const&)>;

class Acceptor : public AcceptorFunc
{
public:
    Acceptor(AcceptorFunc const func, uint64_t const token_count) : AcceptorFunc(func), m_token_count(token_count) {}

    uint64_t getTokenCount() const { return m_token_count; }
private:
    uint64_t m_token_count;

};

template<typename predicate, typename ... predicates>
struct GenericAcceptor : public Acceptor
{
	static inline uint64_t const token_count = GenericAcceptor<predicates...>::token_count + 1;

	GenericAcceptor(int i = 0) : Acceptor([i](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (predicate()(i, currentToken))
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return GenericAcceptor<predicates...>(i + 1)(Cursor(cursor.state, next));
		}
		return AcceptorResult{ .accepted = false, .next = cursor.head };	
	}, token_count)
	{
		
	}
};

template<typename predicate>
struct GenericAcceptor<predicate> : public Acceptor
{
	static inline uint64_t const token_count = 1;

	GenericAcceptor(int i = 0) : Acceptor([i](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (predicate()(i, currentToken))
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return AcceptorResult {.accepted = true, .next = next};
		}
		return AcceptorResult{ .accepted = false, .next = cursor.head };	
	}, 1)
	{

	}
};

struct trivial_predicate
{
	bool operator()(int index, Tokens::const_iterator){ return true; }
};

using AcceptAny = GenericAcceptor<trivial_predicate>;

template<typename pack>
struct pack_predicate
{
	bool operator()(int index, Tokens::const_iterator token) { 
		return token->type == pack::type && token->str == pack::str; 
	}
};

template<typename ... packs>
using AcceptTokens = GenericAcceptor<pack_predicate<packs>...>;
