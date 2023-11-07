#include <stdio.h>
#include "ui.h"

int main() {
	Token tokens[128] = { {INVALID,{'\0'}}};
	bool ret = ParseFile("./testSrc.test", tokens, 128);
	if (ret) {
		printf("PARSED FINISHED\r\n");
	}
	else {
		printf("PARSED UNFINISHED\r\n");
	}

	//char * golden ="322main20122a18256191131hello222b322c522d21";
	char* golden = " 3 22main 20 1 22a 18 256 19 11= 31\"hello\" 32 2 22b 32 3 22c 32 5 22d 32 21";
	char values[1024] = { '\0' };
	int len = 0;
	for (int i = 0; i < 128; ++i) {
		if (tokens[i].type == INVALID) {
			break;
		}
		char value[1024];
		sprintf(value, " %d", tokens[i].type);
		strcat(values, value);
		if (!isKeywordType(tokens[i].type)) {
			sprintf(value, "%s", tokens[i].value);
			strcat(values, value);
		}
	}

	printf("\r\n");
	if (!strcmp(golden, values)) {
		printf("token value correct.");
	}

	return 0;
}