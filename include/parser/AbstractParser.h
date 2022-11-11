#pragma once
#include "../State.h"

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
	State& newState();
	Tokens const& m_tokens;
private:	
	std::vector<std::shared_ptr<State>> m_states;
protected:
	State& m_init;
	State& m_end;
private:
	State * m_head = &m_init;
};

