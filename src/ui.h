#pragma once
#include "Export.h"

#define MAX_TOKEN_LEN 128

typedef enum {
	false = 0,
	true = 1
} bool;

typedef enum {
	INVALID,
	// key words
	CHAR,				// char		1
	SHORT,				// short	2
	INT,				// int		3
	LONG,				// long		4
	FLOAT,				// float	5
	DOUBLE,				// double	6
	ADD,				// +		7
	MINUS,				// -		8
	MULTI,				// *		9
	DIV,				// /		10
	EQUAL,				// =		11
	IF,					// if		12
	ELSE,				// else		13
	WHILE,				// while	14
	FOR,				// for		15
	PARENTHESE_LEFT,	// (		16
	PARENTHESE_RIGHT,	// )		17
	BRACKET_LEFT,		// [		18
	BRACKET_RIGHT,		// ]		19
	BRACE_LEFT,			// {		20
	BRACE_RIGHT,		// }		21
	
	// id
	ID,					// user defined identifier
	
	// value
	BIN,				// 0b...	23
	OCT,				// 0...		24
	DEC,				// ...		25
	HEX,				// 0x...	26
	SIGNED_BIN,			// -0b...	27
	SIGNED_OCT,			// -0...	28
	SIGNED_DEC,			// -...		29
	SIGNED_HEX,			// -0x...	30
	STR					// "..."	31
}TokenType;

typedef struct {
	TokenType			type;
	char				value[MAX_TOKEN_LEN];
}Token;

// bool :		successfully parsed file or not
// fileName:	file to be parsed
// tokens:		memory to store parsed tokens
// maxToken:	capacity of memory to store
bool LEXER_EXPORT ParseFile(const char* fileName, Token* tokens, unsigned maxToken);

bool LEXER_EXPORT isKeywordType(TokenType);