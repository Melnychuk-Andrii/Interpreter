#ifndef TOKEN_TYPE_STRINGS
#define TOKEN_TYPE_STRINGS

#define KEYWORD_COUNT 8
#include <cstring>

extern const char* token_names[] = { "tINT",
									"tPLUS",
									"tMINUS",
									"tMUL",
									"tDIV",
									"tLPAR",
									"tRPAR",
									"tFLOAT",
									"tEOF",
									"tKEYWORD",
									"tEQ",
									"tENDL",
									"tNEQ",
									"tLT",
									"tGT",
									"tLTE",
									"tGTE" };

extern const char* keywords[] = { "move",
								  "turnleft",
								  "turnright",
								  "collect",
								  "place",
								  "AND",
								  "OR",
								  "NOT"};

int get_keyword_id(const char *word)
{
	for (int i = 0; i < KEYWORD_COUNT; i++)
	{
		if (strcmp(word, keywords[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

#endif