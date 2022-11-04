#include "SqlCreateTableParser.h"


bool isNotReserved::operator()(std::string_view const& str)
{
    return std::find(reserved_keywords.begin(), reserved_keywords.end(), str) == reserved_keywords.end();
}

bool isSingleIdentifierTypes::operator()(std::string_view const& str)
{
    return std::find(single_identifier_types.begin(), single_identifier_types.end(), str) != single_identifier_types.end();
}

bool isDoubleIdentifierTypes::operator()(std::string_view const& str)
{
    return std::find(double_identifier_types.begin(), double_identifier_types.end(), str) != double_identifier_types.end();
}

bool isSingleIdentifierSizedTypes::operator()(std::string_view const& str)
{
    return std::find(single_identifier_sized_types.begin(), single_identifier_sized_types.end(), str) != single_identifier_sized_types.end();
}

bool isSingleIdentifierDoubleSizedTypes::operator()(std::string_view const& str)
{
    return std::find(single_identifier_double_sized_types.begin(), single_identifier_double_sized_types.end(), str) != single_identifier_double_sized_types.end();
}

bool isDoubleIdentifierSizedTypes::operator()(std::string_view const& str)
{
    return std::find(double_identifier_sized_types.begin(), double_identifier_sized_types.end(), str) != double_identifier_sized_types.end();
}


SqlCreateTableParser::SqlCreateTableParser(Tokens const& tokens) : AbstractParser(tokens)
{
    State& s1 = newState();
    State& s2 = newState();
    State& s3 = newState();
    State& parAfterCreateTable = newState();
    State& s5 = newState();
    State& s6 = newState();
    State& s7 = newState();
    State& s8 = newState();
    State& s9 = newState();
    State& s10 = newState();
    State& s11 = newState();
    State& s12 = newState();
    State& s13 = newState();

    auto acceptCreateTable = acceptTokens<CreateToken, TableToken>(tokens.cend());
    auto acceptNotReservedPublicIdentifier = acceptPublicIdentifier<isNotReserved>(tokens.cend());
    auto acceptIfNotExists = acceptTokens<IfToken, NotToken, ExistsToken>(tokens.cend());
    auto acceptNotNull = acceptTokens<NotToken, NullToken>(tokens.cend());
    auto acceptDefault = acceptTokens<DefaultToken>(tokens.cend());
    auto acceptLeftPar = acceptTokens<LeftParToken>(tokens.cend());
    auto acceptRightPar = acceptTokens<RightParToken>(tokens.cend());
    auto acceptPrimaryKey = acceptTokens<PrimaryToken, KeyToken>(tokens.cend());
    auto acceptUnique = acceptTokens<UniqueToken>(tokens.cend());
    auto acceptConstraint = acceptTokens<ConstraintToken>(tokens.cend());
    auto acceptRightParSemiColon = acceptTokens<RightParToken, SemiColonToken>(tokens.cend());
    auto acceptPublicSingleIdentifierTypeAcceptor = acceptPublicIdentifier<isSingleIdentifierTypes>(tokens.cend());
    auto acceptPublicSingleIdentifierSizedTypeAcceptor = acceptPublicIdentifier<isSingleIdentifierSizedTypes>(tokens.cend());
    auto acceptInteger = IntegerAcceptor(tokens.cend());
    auto acceptComma = acceptTokens<CommaToken>(tokens.cend());

    m_init.add(acceptCreateTable, s1);
    s1.add(acceptNotReservedPublicIdentifier, s2);
    s2.add(acceptIfNotExists, s3);
    s2.addEpsilon(s3);
    s3.add(acceptLeftPar, parAfterCreateTable);

    parAfterCreateTable.add(acceptNotReservedPublicIdentifier, s5);

    //Type
    s5.add(acceptPublicSingleIdentifierTypeAcceptor, s6, [this](std::string_view token) { m_type = token; });

    //Type(Number)
    s5.add(acceptPublicSingleIdentifierSizedTypeAcceptor, s7, [this](std::string_view token) { m_type = token; });
    s7.add(acceptLeftPar, s8);
    s8.add(acceptInteger, s9);
    s9.add(acceptRightPar, s6);


    s6.add(acceptNotNull, s10);
    s6.addEpsilon(s10);
    s10.add(acceptDefault, s11);
    s10.addEpsilon(s12);
    s11.add(DefaultValueAcceptator(tokens.cend(), this), s12);
    s12.add(acceptComma, parAfterCreateTable);
    s12.add(acceptRightParSemiColon, s13);
    s13.addEpsilon(m_init);
    s13.addEpsilon(m_end);
}
