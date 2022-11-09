#include "../../include/State.h"

State::State()
{

}


void State::add(uint64_t token_count, Acceptor acceptor, State const& state)
{
	m_nexts.emplace_back(std::make_tuple(token_count, acceptor, &state));
}

void State::addEpsilon(State const& state)
{
	m_nexts.emplace_back(std::make_tuple(0, [](Cursor const& cursor) { return AcceptorResult{ .accepted = true, .next = cursor.head }; }, &state));
}

std::vector<Cursor> State::getNextCursors(Cursor const& current, Tokens const& tokens) const
{
	std::vector<Cursor> nextCursors;
	for (auto& cursor : m_nexts)
	{
		auto token_count = std::get<uint64_t>(cursor);
		if(token_count > tokens.cend() - current.head)//No enough tokens to accept
		{
			continue;
		}
		
		//Here we are sure that we can increment current.head at least token_count times
		AcceptorResult result = std::get<Acceptor>(cursor)(current);
		
		//If the next state is accepted
		if (result.accepted)
		{
			//Push it to the list of the next possible states
			nextCursors.push_back(Cursor(std::get<State const * const>(cursor), result.next));
		}
	}
	return nextCursors;
}