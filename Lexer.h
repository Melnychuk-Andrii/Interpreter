#ifndef LEXER
#define LEXER

#include "Token.h"
#include "Position.h"
#include <cstring>

#define TOKEN_LEN 10000
#define DELIM " \t\n\r"
#define DIGITS "0123456789"

class Lexer
{
private:
	std::string text;
	Position position;
	char cur_char;
	Token *tokens;
	int token_count;

public:
	Lexer(){};
	Lexer(char *x){text = x; position = Position(); cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN];};
	Lexer(std::string x){text = x; position = Position(); cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN];};
	void make_tokens();
	void advance();
	Token* returnTokens();
    int returnTokenCount(){return token_count;}
	Token make_number_token();
	std::string print_tokens();
};

#endif
