#ifndef ParserH
#define ParserH

#include "Token.h"
#include "Node.h"
#include "Error_class.h"

class Parser
{
private:
	Token *tokens, *cur_tok;
	int tok_len;
	int tok_idx;
	Err *errors;

public:
	Parser(){};
	Parser(Token *tok, int tok_c, Err *e) { tok_len = tok_c; tokens = tok; tok_idx = -1; errors = e;}
	Token* advance();
	SNode* factor();
	SNode* term();
	SNode* expr();
	SNode* c_expr();
	SNode* a_expr();
	SNode* if_expr();
	SNode* while_expr();
	SNode* event_expr();
	SNode* oper_expr();
	SNode* func_expr();
	SNode* parse();
};

#endif
