#include "State.h"

State::State()
{

}


void State::add(Acceptor acceptator, State const& state, Action action)
{
	m_nexts.emplace_back(std::make_tuple(acceptator, &state, action));
}

void State::addEpsilon(State const& state)
{
	m_nexts.emplace_back(std::make_tuple([](Cursor const& cursor) { return AcceptorResult{ .accepted = true, .next = cursor.head }; }, &state, Action()));
}

std::vector<Cursor> State::getNextCursors(Cursor const& current) const
{
	std::vector<Cursor> nextCursors;
	for (auto& cursor : m_nexts)
	{
		AcceptorResult result = std::get<0>(cursor)(current);
		
		if (result.accepted)
		{
			nextCursors.push_back(Cursor(std::get<1>(cursor), result.next));
			decltype(auto) customFunc = std::get<2>(cursor);
			if(customFunc)
				customFunc(current.head->str);
		}
	}
	return nextCursors;
}