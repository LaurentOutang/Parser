#include "../../include/parser/SqlCreateTableParser.h"
#include "../../include/SqlTokens.h"

SqlCreateTableParser::SqlCreateTableParser(Tokens const& tokens) : 
    AbstractParser(tokens),
    m_createDefinitionParser(tokens)
{
    State& s1 = newState();
    State& s2 = newState();
    State& s3 = newState();
    State& parAfterCreateTable = newState();
    
    State& s12 = newState();
    State& s13 = newState();

    auto acceptCreateTable = acceptTokens<CreateToken, TableToken>();
    auto acceptNotReservedPublicIdentifier = acceptPublicIdentifier<isNotReserved>();
    auto acceptIfNotExists = acceptTokens<IfToken, NotToken, ExistsToken>();
    auto acceptNotNull = acceptTokens<NotToken, NullToken>();
    auto acceptDefault = acceptTokens<DefaultToken>();
    auto acceptLeftPar = acceptTokens<LeftParToken>();
    auto acceptRightPar = acceptTokens<RightParToken>();
    auto acceptPrimaryKey = acceptTokens<PrimaryToken, KeyToken>();
    auto acceptUnique = acceptTokens<UniqueToken>();
    auto acceptConstraint = acceptTokens<ConstraintToken>();
    auto acceptRightParSemiColon = acceptTokens<RightParToken, SemiColonToken>();
    auto acceptInteger = IntegerAcceptor();
    auto acceptComma = acceptTokens<CommaToken>();

    m_init.add(2, acceptCreateTable, s1);
    s1.add(1, acceptNotReservedPublicIdentifier, s2);
    s2.add(3, acceptIfNotExists, s3);
    s2.addEpsilon(s3);
    s3.add(1, acceptLeftPar, parAfterCreateTable);

    parAfterCreateTable.addEpsilon(m_createDefinitionParser.getInit());
    m_createDefinitionParser.getEnd().addEpsilon(s12);

    s12.add(1, acceptComma, parAfterCreateTable);
    s12.add(2, acceptRightParSemiColon, s13);
    s13.addEpsilon(m_init);
    s13.addEpsilon(m_end);
}
