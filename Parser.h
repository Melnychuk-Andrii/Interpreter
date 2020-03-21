#ifndef ParserH
#define ParserH

#include "Token.h"
#include "Node.h"

class Parser
{
private:
	Token *tokens, *cur_tok;
	int tok_len;
	int tok_idx;

public:
	Parser(){};
	Parser(Token *tok, int tok_c) { tok_len = tok_c; tokens = tok; tok_idx = -1; }
	Token* advance();
	SNode* factor();
	SNode* term();
	SNode* expr();
	SNode* parse();
};

#endif
