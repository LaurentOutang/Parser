#ifndef __ACCEPTOR__
#define __ACCEPTOR__
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

struct acceptAny : public Acceptor
{
	acceptAny() : Acceptor([](Cursor const& cursor) {
        auto currentToken = cursor.head;
		Tokens::const_iterator next = cursor.head;
		++next;
		return AcceptorResult{ .accepted = true, .next = next };
    }, 1)
	{

	}
};

template<typename pack, typename ... packs>
struct acceptTokens : public Acceptor
{
	static inline uint64_t const token_count = acceptTokens<packs...>::token_count + 1;
	acceptTokens() : Acceptor([](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == pack::type && currentToken->str == pack::str)
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return acceptTokens<packs...>()(Cursor(cursor.state, next));
		}
		else return AcceptorResult{ .accepted = false, .next = cursor.head };
	}, token_count)
	{
		
	}
};

template<typename pack>
struct acceptTokens<pack> : public Acceptor
{
	static inline uint64_t const token_count = 1;

	acceptTokens() : Acceptor([](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (currentToken->type == pack::type && currentToken->str == pack::str)
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

#endif