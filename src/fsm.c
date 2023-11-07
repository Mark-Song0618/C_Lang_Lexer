#include "fsm.h"
#include "lexer.h"
#include <stdio.h>

static unsigned			parsedToken			= 0;
static bool				eof					= false;
static bool				isSigned			= false;
static STATUS			currStatus			= ST_START;
static Token*			result				= NULL;
static char				buf[MAX_TOKEN_LEN]	= { '\0' };
static unsigned			pos					= 0;

STATUS transit(STATUS status , char c)
{
	return _transit[status](c);
}

bool acceptChar(char c) {
	STATUS ret = transit(currStatus, c);
	if (ret != ST_UNRECOG) {
		buf[pos++] = c;
		currStatus = ret;
		return true;
	}
	return false;
}

bool acceptToken() {
	if (*buf == '\0') {
		return true;	// nothing to parse
	}
	if (isComment(currStatus)) {
		goto RESET;	// comment need not to parse
	}
	else if (_typeTable[currStatus] == INVALID) {
		return false;	// not a token
	}
	else {
		// store recognized token
		// todo, identify key word
		Token token;
		TokenType origType = _typeTable[currStatus];
		if (origType == ID) {
			TokenType kw = isKeyword(buf);
			if (kw != INVALID) {
				token.type = kw;
			}
			else {
				token.type = origType;
				strcpy(token.value, buf);
			}
		}
		else {
			if (isSigned == true) {
				token.type = signedType(origType);
				strcpy(token.value, buf);
			}
			else {
				token.type = origType;
				strcpy(token.value, buf);
			}
		}
		result[parsedToken++] = token;
		
RESET:
		strset(buf, '\0');
		pos = 0;
		currStatus = ST_START;
		isSigned   = false;
		return true;
	}
}

bool fsm_run(FILE* srcFile, Token* tokens, unsigned maxToken)
{
	result = tokens;
// 当文件没有解析完，并且token没有填满，就持续地解析
	while (parsedToken != maxToken && !eof) {
		char c = fgetc(srcFile);
		bool ret = acceptChar(c);
		if (ret) {
			continue;
		}
		else {
			ret = acceptToken();
			if (!ret) {
				goto UNRECOGNIZE;
			}
			if (isSplitter(c)) {
				continue;
			}
			if (c == EOF) {
				eof = true;
				break;
			}
			ret = acceptChar(c);
			if (!ret) {
				goto UNRECOGNIZE;
			}

		}
	}

	if (!eof) {
		printf("Buffer readched limit, token recognize stops\r\n");
	}
	printf("Token Recognized successfully\r\n");
	fclose(srcFile);

	return true;

UNRECOGNIZE:
	printf("unrecognizable character after: %s\r\n", buf);
	fclose(srcFile);
	return false;	
}