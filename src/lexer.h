#include "ui.h"
#include <string.h>

// internal data and functions
typedef enum {
	ST_START = 0,
	ST_ID,
	ST_BIN_OCT_HEX,
	ST_BIN_SIGN,
	ST_HEX_SIGN,
	ST_BIN,
	ST_OCT,
	ST_HEX,
	ST_DEC,
	ST_PARENTHESE_LEFT,
	ST_PARENTHESE_RIGHT,
	ST_BRACKET_LEFT,
	ST_BRACKET_RIGHT,
	ST_BRACE_LEFT,
	ST_BRACE_RIGHT,
	ST_ADD,
	ST_MINUS,
	ST_MULTI,
	ST_DIV,
	ST_EQU,
	ST_UNCLOSE_STR,
	ST_STR,
	ST_UNRECOG,
	TOTAL_STATUS
} STATUS;

TokenType typeTable[TOTAL_STATUS] =
{
	INVALID,
	ID,
	INVALID,
	INVALID,
	INVALID,
	BIN,
	OCT,
	HEX,
	DEC,
	PARENTHESE_LEFT,
	PARENTHESE_RIGHT,
	BRACKET_LEFT, 
	BRACKET_RIGHT,
	BRACE_LEFT,
	BRACE_RIGHT,
	ADD,
	MINUS,
	MULTI,
	DIV,
	EQUAL,
	INVALID,
	STR,
	INVALID,
};

typedef STATUS	(*transitHandler)	(char);

STATUS transit_start(char);
STATUS transit_ID(char);
STATUS transit_BIN_OCT_HEX(char);
STATUS transit_BIN_SIGN(char);
STATUS transit_HEX_SIGN(char);
STATUS transit_BIN(char);
STATUS transit_OCT(char);
STATUS transit_HEX(char);
STATUS transit_DEC(char);
STATUS transit_SINGLE_CHAR(char);
STATUS transit_UNCLOSE_STR(char);

transitHandler	  _transit[TOTAL_STATUS] = { transit_start,
											transit_ID,
											transit_BIN_OCT_HEX,
											transit_BIN_SIGN,
											transit_HEX_SIGN,
											transit_BIN,
											transit_OCT,
											transit_HEX,
											transit_DEC,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_SINGLE_CHAR,
											transit_UNCLOSE_STR,
											transit_SINGLE_CHAR,
											NULL};

bool	acceptChar(char c);

bool	acceptToken();

bool	isSplitter(char c);

STATUS	transit(STATUS, char);

bool	isAlpha(char);

bool	isUnderline(char);

bool	isBinary(char);

bool	isOctal(char);

bool	isDecimal(char);

bool	isHexadecimal(char);

bool	isKeyword(const char*);

TokenType signedType(TokenType);
