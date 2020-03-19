#ifndef LEXER
#define LEXER

#include "Tokens.h"
#include <cstring>

#define TOKEN_LEN 10000
#define DELIM " \t\n\r"
#define DIGITS "0123456789"

class Lexer
{
private:
	std::string text;
	int position;
	char cur_char;
	Token *tokens;
	int token_count;

public:
	Lexer(){};
	Lexer(char *x){text = x; position = -1; cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN];};
	Lexer(std::string x){text = x; position = -1; cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN];};
	void advance();
	void make_tokens();
	Token make_number_token();
	std::string print_tokens();
};

#endif
