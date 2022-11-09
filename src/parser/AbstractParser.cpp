#include "../../include/parser/AbstractParser.h"

AbstractParser::AbstractParser(Tokens const& tokens) :
	m_tokens(tokens),
	m_init{newState()},
	m_end{newState()}
{

}

State& AbstractParser::newState()
{
	std::shared_ptr<State> ptr = std::make_shared<State>();
	m_states.push_back(std::move(ptr));
	return *m_states.back().get();
}
