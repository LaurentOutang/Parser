#include "SharedParser.h"

SharedParser::SharedParser(Tokens const& token) : AbstractParser(token)
{

}

void SharedParser::bind(AbstractParser const& parser)
{
	m_end.addEpsilon(parser.getInit());
}