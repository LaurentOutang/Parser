#include "../../include/parser/TestParser.h"
#include "../../include/acceptor/Acceptor.h"

TestParser::TestParser(Tokens const& tokens) : Parser(tokens)
{
	State& afterLeftParState = newState();
	State& afterRightParOrNothingState = newState();
	using LeftParToken = Pack<test::TestTokenType::PUNCTUATOR, "(">;
	using StarToken = Pack<test::TestTokenType::OPERATOR, "*">;
	using RightParToken = Pack<test::TestTokenType::PUNCTUATOR, ")">;

	auto leftParAcceptor = acceptTokens<LeftParToken>{};
	auto chainAcceptor = acceptTokens<RightParToken, StarToken>{};
	auto rightParAcceptor = acceptTokens<StarToken>{};

	m_init.add(leftParAcceptor, afterLeftParState);
	afterLeftParState.add(chainAcceptor, afterRightParOrNothingState);
	afterLeftParState.add(rightParAcceptor, afterRightParOrNothingState);
	afterRightParOrNothingState.addEpsilon(m_end);
	afterRightParOrNothingState.addEpsilon(m_init);
}
