#pragma once
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include "Token.h"
#include "acceptor/Acceptor.h"



class State
{
	friend struct Cursor;
public:

	State();
	void add(Acceptor &, State const&);
	void addEpsilon(State const&);
	std::vector<Cursor> getNextCursors(Cursor const& current, Tokens const& token) const;
private:
	std::vector<std::tuple<Acceptor *, State const * const>> m_nexts;//First param must be the count of tokens accepted by Acceptor
};

