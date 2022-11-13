#include "../../include/parser/AbstractParser.h"

AbstractParser::AbstractParser(Tokens const& tokens) :
	m_tokens(tokens),
	m_init{*m_states.find("init")->second},
	m_end{*m_states.find("end")->second}
{

}

void AbstractParser::connect(std::string source, std::string sink, Acceptor const& acceptor)
{
	auto sourceIt = m_states.find(source);
	auto sinkIt = m_states.find(sink);
	if(sinkIt == m_states.end())
	{
		sinkIt = m_states.insert(std::make_pair(sink, std::make_shared<State>())).first;
	}
	sourceIt->second->add(acceptor, *sinkIt->second);
}

void AbstractParser::connect(std::string source, std::string sink)
{
	auto sourceIt = m_states.find(source);
	auto sinkIt = m_states.find(sink);
	if(sinkIt == m_states.end())
	{
		sinkIt = m_states.insert(std::make_pair(sink, std::make_shared<State>())).first;
	}
	sourceIt->second->addEpsilon(*sinkIt->second);
}


void AbstractParser::connect(std::string source, std::string sink, AbstractParser const& parser)
{
	auto sourceIt = m_states.find(source);
	auto sinkIt = m_states.find(sink);
	if(sinkIt == m_states.end())
	{
		sinkIt = m_states.insert(std::make_pair(sink, std::make_shared<State>())).first;
	}
	sourceIt->second->addEpsilon(parser.getInit());
    parser.getEnd().addEpsilon(*sinkIt->second);
}