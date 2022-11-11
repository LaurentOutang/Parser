#pragma once

class State;

struct Cursor
{
	State const * state;
	Tokens::const_iterator head;
};