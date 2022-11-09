#pragma once
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include "Token.h"

struct AcceptorResult
{
	bool accepted;
	Tokens::const_iterator next;
};

class State;
struct Cursor;

using Acceptor = std::function<AcceptorResult(Cursor const&)>;

using Action = std::function<void(std::string_view const&)>;

struct Cursor
{
	State const * state;
	Tokens::const_iterator head;
};

class State
{
	friend struct Cursor;
public:

	State();
	void add(uint64_t, Acceptor, State const&);
	void addEpsilon(State const&);
	std::vector<Cursor> getNextCursors(Cursor const& current, Tokens const& token) const;
private:
	std::vector<std::tuple<uint64_t, Acceptor, State const * const>> m_nexts;//First param must be the count of tokens accepted by Acceptor
};

