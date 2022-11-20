#pragma once
#include "../SqlTokens.h"
#include "../State.h"
#include <algorithm>

struct SqlAcceptor
{
	struct IntegerAcceptor : public GenericAcceptor
	{
		IntegerAcceptor() : GenericAcceptor({std::make_shared<std::vector<std::function<bool(Tokens::const_iterator)>>>( {
			[](Tokens::const_iterator token) { return token->type == TokenType::INTEGER; }
		})})
		{
		}
	} INTEGER_ACCEPTOR;

	struct ArbitraryPrecisionNumberAcceptor : public GenericAcceptor
	{
		ArbitraryPrecisionNumberAcceptor() : GenericAcceptor({std::make_shared<std::vector<std::function<bool(Tokens::const_iterator)>>>( {
			[](Tokens::const_iterator token) { return token->type == TokenType::INTEGER || 
				token->type == TokenType::FLOATING ||
				token->type == TokenType::LITERAL && (token->str == "Nan" || token->str == "Infinity" || token->str == "-Infinity"); 
			}
		})})
		{
		}
	} ARBITRARY_PRECISION_NUMBER_ACCEPTOR;

	struct floating_point_predicate
	{
		bool operator()(Tokens::const_iterator token){ return token->type == TokenType::FLOATING; }
	};
	using FloatingPointAcceptor = GenericAcceptor<floating_point_predicate>;

	static bool find_in_vector(std::vector<std::vector<std::string_view>> const& vector, int index, std::string_view str)
	{
		std::string lower;
		lower.resize(str.size());
		std::transform(str.cbegin(), str.cend(), lower.begin(), [](char c){return std::tolower(c);});
		auto it = std::find_if(vector.cbegin(), vector.cend(), [&](std::vector<std::string_view> const& vec){
			if(vec.size() > index)
				return vec[index] == lower;
			return false;
		});
		return it != vector.end();
	}

	static inline const std::vector<std::vector<std::string_view>> integer_types {
		{"smallint"}, {"integer"}, {"bigint"}, {"int"}
	};
	
	struct integer_type_predicate
	{
		bool operator()(Tokens::const_iterator token){ 
			std::string lower;
			lower.resize(token->str.size());
			std::transform(token->str.cbegin(), token->str.cend(), lower.begin(), [](char c){ return std::tolower(c); });
			return token->type == TokenType::IDENTIFIER && 
			find_in_vector(integer_types, 0, token->str);
		}
	};
	using IntegerTypeAcceptor = GenericAcceptor<integer_type_predicate>;

	static inline const std::vector<std::vector<std::string_view>> arbitrary_precision_number_types {
		{"numeric"}
	};

	struct arbitrary_precision_number_type_predicate
	{
		bool operator()(Tokens::const_iterator token){ 
			std::string lower;
			lower.resize(token->str.size());
			std::transform(token->str.cbegin(), token->str.cend(), lower.begin(), [](char c){return std::tolower(c);});
			return token->type == TokenType::IDENTIFIER && 
			find_in_vector(arbitrary_precision_number_types, token->str);
		}
	};
	using ArbitraryPrecisionNumberTypeAcceptor = GenericAcceptor<arbitrary_precision_number_type_predicate>;

	static inline const std::vector<std::vector<std::string_view>> floating_point_types {
		{"real"}
	};
	struct floating_point_type_predicate
	{
		bool operator()(Tokens::const_iterator token){ 
			std::string lower;
			lower.resize(token->str.size());
			std::transform(token->str.cbegin(), token->str.cend(), lower.begin(), [](char c){return std::tolower(c);});
			return token->type == TokenType::IDENTIFIER && 
			find_in_vector(floating_point_types, 0, token->str);
		}
	};
	using FloatingPointTypeAcceptor = GenericAcceptor<floating_point_type_predicate>;

	static inline const std::vector<std::vector<std::string_view>> floating_point_types2 {
		{"double", "precision"}
	};

	struct FloatingPointType2Acceptor : public Acceptor
	{
		FloatingPointType2Acceptor() : Acceptor([](size_t index, Cursor const& cursor){
			auto currentToken = cursor.head;
			for(auto& vec : floating_point_types2)
			{
				auto locToken = currentToken;
				int i = 0;
				for(auto& str : vec)
				{
					std::string lower;
					lower.resize(locToken->str.size());
					std::transform(locToken->str.cbegin(), locToken->str.cend(), lower.begin(), [](char c){return std::tolower(c);});
					
					if(locToken->type != TokenType::IDENTIFIER || lower != str)
					{
						continue;
					}
					++locToken;
					++i;
				}

				if(i == vec.size())
				{
					return AcceptorResult {.accepted = true, .next = locToken};	
				}
			}
			return AcceptorResult {.accepted = false, .next = currentToken};	
		}, 2)
		{
			
		}
	};

	static inline const std::vector<std::vector<std::string_view>> serial_types {
		{"samllserial"}, {"serial"}, {"bigserial"}
	};
	struct serial_type_predicate
	{
		bool operator()(Tokens::const_iterator token){ 
			std::string lower;
			lower.resize(token->str.size());
			std::transform(token->str.cbegin(), token->str.cend(), lower.begin(), [](char c){return std::tolower(c);});
			return token->type == TokenType::IDENTIFIER && 
			find_in_vector(serial_types, 0, token->str);
		}
	};
	using SerialTypeAcceptor = GenericAcceptor<serial_type_predicate>;

	struct free_identifier_predicate
	{
		bool operator()(Tokens::const_iterator token){
			return 
			!find_in_vector(integer_types, 0, token->str) &&
			!find_in_vector(arbitrary_precision_number_types, 0, token->str) &&
			!find_in_vector(floating_point_types, 0, token->str) &&
			!find_in_vector(serial_types, 0, token->str);
		}
	};
	using FreeIdentifierAcceptor = GenericAcceptor<free_identifier_predicate>;

/* 	static inline std::vector<std::string_view> single_identifier_types{
		"BIGINT",
		"BOOLEAN",
		"BOX",
		"BYTEA",
		"CIDR",
		"CIRCLE",
		"DATE",
		"INET",
		"INTEGER",
		"JSON",
		"JSONB",
		"LINE",
		"LSEG",
		"MACADDR",
		"MONEY",
		"PATH",
		"PG_LSN",
		"POINT",
		"POLYGON",
		"REAL",
		"SMALLINT",
		"SMALLSERIAL",
		"SERIAL",
		"TEXT",
		"TSQUERY",
		"TSVECTOR",
		"TXID_SNAPSHOT",
		"UUID",
		"XML",
		"INT8",
		"SERIAL8",
		"BOOL",
		"FLOAT8",
		"INT",
		"INT4",
		"FLOAT4",
		"INT2",
		"SERIAL2",
		"SERIAL4",
		"BIGSERIAL",
		"TIMETZ",
		"TIMESTAMPTZ",
		"VARCHAR"
	}; */
public:
	static inline AcceptAny anyToken;

	static inline FreeIdentifierAcceptor freeIdentifier;

    static inline IntegerAcceptor integer;
	static inline FloatingPointAcceptor floatingPoint;
	static inline ArbitraryPrecisionNumberAcceptor arbitraryPrecisionNumber;

	static inline IntegerTypeAcceptor integerType;
	static inline FloatingPointTypeAcceptor floatingPointType;
	static inline FloatingPointType2Acceptor floatingPointType2;
	static inline ArbitraryPrecisionNumberTypeAcceptor arbitraryPrecisionNumberType;	
	static inline SerialTypeAcceptor serialType;

    static inline AcceptTokens<CommaToken> comma;
    static inline AcceptTokens<UniqueToken> unique;
    static inline AcceptTokens<DefaultToken> Default;
    static inline AcceptTokens<LeftParToken> leftPar;
    static inline AcceptTokens<RightParToken> rightPar;
    static inline AcceptTokens<ConstraintToken> constraint;
    static inline AcceptTokens<NotToken, NullToken> notNull;
    static inline AcceptTokens<CreateToken, TableToken> createTable;
    static inline AcceptTokens<PrimaryToken, KeyToken> primaryKey;
    static inline AcceptTokens<IfToken, NotToken, ExistsToken> ifNotExists;
    static inline AcceptTokens<RightParToken, SemiColonToken> rightParSemiColon;


};