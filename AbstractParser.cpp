#include "AbstractParser.h"

#ifdef _DEBUG
#include <iostream>
#endif

AbstractParser::AbstractParser(Tokens const& tokens) :
	m_tokens(tokens),
	m_init{newState()},
	m_end{newState()}
{

}

AbstractParser& AbstractParser::then(Acceptor acceptor, Action&& action = Action(), bool advance = true)
{
	State& next = newState();
	m_head->add(acceptor, next, action);
	if (advance)
		m_head = &next;
	return *this;
}

State& AbstractParser::newState()
{
	m_states.push_back(std::make_unique<State>());
	return *m_states.back().get();
}
