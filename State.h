#pragma once
#include <vector>
#include <string>
#include <functional>
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
	State const * const state;
	Tokens::const_iterator head;
};

class State
{
	friend struct Cursor;
public:

	State();
	void add(Acceptor, State const&, Action = Action());
	void addEpsilon(State const&);
	std::vector<Cursor> getNextCursors(Cursor const& current) const;
private:
	std::vector<std::tuple<Acceptor,State const * const, Action>> m_nexts;
};

