#ifndef LEXER
#define LEXER

#include "Token.h"
#include "Position.h"
#include "Error_class.h"
#include <cstring>

#define TOKEN_LEN 10000
#define DELIM " \t\r\n"
#define DIGITS "0123456789"

class Lexer
{
private:
	std::string text;
	Position position;
	char cur_char;
	Token *tokens;
	int token_count;
	Err *errors;

public:
	Lexer(){};
	Lexer(char *x, Err *e){text = x; position = Position(); cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN]; errors = e;};
	Lexer(std::string x, Err *e){text = x; position = Position(); cur_char = 0; token_count = 0; tokens=new Token[TOKEN_LEN];errors = e;};
	void make_tokens();
	void advance();
	Token* returnTokens();
	int returnTokenCount(){return token_count;}
	Token make_number_token();
	Token make_keyword_token();
	Token make_not_eq_token();
	Token make_greater_token();
	Token make_less_token();
	std::string print_tokens();
};

#endif
