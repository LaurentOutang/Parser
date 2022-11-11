#include "../../include/State.h"

State::State()
{

}


void State::add(Acceptor const& acceptor, State const& state)
{
	m_nexts.emplace_back(std::make_tuple(&acceptor, &state));
}

void State::addEpsilon(State const& state)
{
	m_nexts.emplace_back(std::make_tuple(&State::epsilon_acceptor, &state));
}

std::vector<Cursor> State::getNextCursors(Cursor const& current, Tokens const& tokens) const
{
	std::vector<Cursor> nextCursors;
	for (auto& cursor : m_nexts)
	{
		auto const acceptor = *std::get<Acceptor const*>(cursor);
		auto token_count = acceptor.getTokenCount();
		if(token_count > tokens.cend() - current.head)//No enough tokens to accept
		{
			continue;
		}
		
		//Here we are sure that we can increment current.head at least token_count times
		AcceptorResult result = acceptor(current);
		
		//If the next state is accepted
		if (result.accepted)
		{
			//Push it to the list of the next possible states
			nextCursors.push_back(Cursor(std::get<State const * const>(cursor), result.next));
		}
	}
	return nextCursors;
}