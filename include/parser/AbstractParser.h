#pragma once
#include "../State.h"
#include <string>
#include <map>

class ParseError {};

class ReachFinalState {};

class EndParseTokensInInvalidStates {};

class AbtractSyntaxTree {};

class AbstractParser
{
public:
	AbstractParser(Tokens const& token);	

	State& getInit() const { return m_init; }
	State& getEnd() const { return m_end; }
protected:
	void connect(std::string source, std::string sink, Acceptor const& acceptor);
	void connect(std::string source, std::string sink);
	void connect(std::string source, std::string sink, AbstractParser const& parser);
protected:
	Tokens const& m_tokens;	
private:	
	std::map<std::string, std::shared_ptr<State>> m_states = {{"init", std::make_shared<State>()}, {"end", std::make_shared<State>()}};
protected:
	State& m_init;
	State& m_end;
private:
	State * m_head = &m_init;
};

