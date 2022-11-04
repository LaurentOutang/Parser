#include "SqlParser.h"
#include "SqlLexer.h"
#include <iostream>

Tokens::const_iterator begin;

int main()
{
	std::string code =	"CREATE TABLE maTable IF NOT EXISTS			     \n("
						"id SERIAL,"
						"age INTEGER NOT NULL DEFAULT 23,"
						"nom VARCHAR"
						"); \n";/*
						"(\n"
						"mon_nom_de_variable BIGINT NOT NULL,\n"
						"voiliVoilou BOOLEAN\n"
						");";*/

	SqlLexer lexer(code);
	try
	{
		Tokens tokens = lexer.tokenize();
		SqlParser parser(tokens);
		AbtractSyntaxTree ast = parser.parse();
		std::cout << "Correctly parsed !! " << std::endl;
	}
	catch (UnknownTokenError const& unknownTokenError)
	{
		std::cout << "Unknown token error!! " << std::endl;
	}
	catch (ParseError const& parseError)
	{
		std::cout << "Failed to parse !! " << std::endl;
	}
	return 0;
}