#include "../../include/parser/SqlParser.h"
#include "../../include/lexer/SqlLexer.h"

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
		std::cerr << "Unknown token error!! " << std::endl;
	}
	catch (ParseError const& parseError)
	{
		std::cerr << "Failed to parse !! " << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}
	std::cout << "Program finished" << std::endl;
	return 0;
}