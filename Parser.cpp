#include "Parser.h"

Parser::Parser(Tokens const& tokens) : AbstractParser(tokens)
{
	m_cursors.emplace_back(&m_init, m_tokens.cbegin());
}

AbtractSyntaxTree Parser::parse()
{
	AbtractSyntaxTree tree;
	std::vector<Cursor> nextCursors;
	do
	{
		nextCursors.clear();
		for (Cursor& cursor : m_cursors)
		{
			std::vector<Cursor> localNextCursors = cursor.state->getNextCursors(cursor);
			for (Cursor& localNextState : localNextCursors)
			{
				nextCursors.push_back(localNextState);
			}
		}
		m_cursors.swap(nextCursors);
	} while (!reachedEnd() && !m_cursors.empty());
	if (m_cursors.empty())
	{
		throw ParseError();
	}
	else return tree;
}

bool Parser::reachedEnd() const
{
	for (auto& cursor : m_cursors)
	{
		Tokens::const_iterator next = cursor.head;
		if (cursor.head == m_tokens.cend() && cursor.state == &m_end)
			return true;
	}
	return false;
}