#pragma once
#include <functional>
#include "../Token.h"
#include "../Cursor.h"

struct AcceptorResult
{
	bool accepted;
	Tokens::const_iterator next;
};

using RequestFunc = std::function<AcceptorResult(Cursor const&)>;

class Request : public RequestFunc
{
public:
	Request(RequestFunc&& req, std::function<size_t(void)>&& token_count = []{return 1;}) : RequestFunc(std::move(req)), m_token_count(std::move(token_count)) {}

	size_t getTokenCount() const {return m_token_count();};
private:
	std::function<size_t(void)> m_token_count;
};

using Requests = std::vector<Request>;

class Acceptor : public Requests
{
public:
	using iterator = Requests::iterator;
	using const_iterator = Requests::const_iterator;
};

struct GenericAcceptor : public Acceptor
{
	GenericAcceptor(std::vector<std::shared_ptr<std::vector<std::function<bool(Tokens::const_iterator)>>>> tokens)
	{
		for(auto& tokenv : tokens)
		{
			emplace_back([=](Cursor const& cursor) {
				auto currentToken = cursor.head;

				for(auto& tokenF : *tokenv)
				{
					if(tokenF(currentToken))
					{
						++currentToken;
					}
					else break;
				}
				if(currentToken - cursor.head == tokenv->size())
					return AcceptorResult { .accepted = true, .next = currentToken };
				else 
					return AcceptorResult{ .accepted = false, .next = cursor.head };	
			}, [=]{ return tokenv->size(); });
		}		
	}
};

struct VectorAcceptor : public Acceptor
{
	VectorAcceptor(std::vector<std::shared_ptr<Tokens>> tokens)
	{
		for(auto& tokenv : tokens)
		{
			emplace_back([=](Cursor const& cursor) {
				auto currentToken = cursor.head;

				for(Token& token : *tokenv)
				{
					if(token == *currentToken)
					{
						++currentToken;
					}
					else break;
				}
				if(currentToken - cursor.head == tokenv->size())
					return AcceptorResult { .accepted = true, .next = currentToken };
				else
					return AcceptorResult { .accepted = false, .next = cursor.head };	
			}, [=]{ return tokenv->size(); });
		}		
	}
};

struct EpsilonAcceptor : public Acceptor
{
	EpsilonAcceptor()
	{
		emplace_back([](Cursor const& cursor) { return AcceptorResult { .accepted = true, .next = cursor.head }; }, []{ return 0; });
	}
} EPSILON_ACCEPTOR;
/* 
struct GenericAcceptor : public Acceptor
{
	GenericAcceptor(auto predicate) : Acceptor([](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (predicate()(currentToken))
		{
			Tokens::const_iterator next = cursor.head;
			++next;
			return GenericAcceptor<then_predicates...>()(Cursor(cursor.state, next));
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

	GenericAcceptor() : Acceptor([](Cursor const& cursor) {
		auto currentToken = cursor.head;
		if (predicate()(currentToken))
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
	bool operator()(Tokens::const_iterator){ return true; }
};

using AcceptAny = GenericAcceptor<trivial_predicate>;

template<typename pack>
struct pack_predicate
{
	bool operator()(Tokens::const_iterator token) { 
		return token->type == pack::type && token->str == pack::str; 
	}
};

template<typename ... packs>
using AcceptTokens = GenericAcceptor<pack_predicate<packs>...>;
 */