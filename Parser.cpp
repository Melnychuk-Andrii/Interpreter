#include "Parser.h"
#include "Token_type_strings.h"

Token* Parser::advance()
{
	tok_idx++;

	if (tok_idx < tok_len) {
		cur_tok = tokens + tok_idx;
	}

	return cur_tok;
}

SNode* Parser::factor()
{
	Token *num_tok = cur_tok;

	if (cur_tok->getType() == token_type::tPLUS ||
		cur_tok->getType() == token_type::tMINUS)
	{
		advance();
		return  crNodeChild(factor(), NULL, num_tok, num_tok->getPos());
	}else if (cur_tok->getType() == token_type::tINT ||
			  cur_tok->getType() == token_type::tFLOAT)
	{
		advance();
		return createNode(num_tok, num_tok->getPos());
	}else if (cur_tok->getType() == token_type::tLPAR)
	{
		advance();
		SNode *exprr = expr();
		if (cur_tok->getType() == token_type::tRPAR) {
			  advance();
			  return exprr;
		}else
		{
			errors->parseErr();
			std::string x = "";
			errors->addErr(x + "Line: " + std::to_string(cur_tok->getPos().getLine()) + " column: " +
						   std::to_string(cur_tok->getPos().getCol()) + ". Expected a ')'.");
			return NULL;
		}
	}

	errors->parseErr();
	std::string x = "";
	errors->addErr(x + "Line: " + std::to_string(num_tok->getPos().getLine()) + " column: " +
						   std::to_string(num_tok->getPos().getCol()) + ". Expected an int or a float.");
	return NULL;
}

SNode* Parser::term()
{
	SNode *right, *left = factor();
	Token op_tok;

	while (cur_tok->getType() == token_type::tMUL ||
		   cur_tok->getType() == token_type::tDIV)
	{
		op_tok = *cur_tok;
		advance();
		right = factor();
		left = crNodeChild(left, right, op_tok, op_tok.getPos());
	}

	return left;
}

SNode* Parser::expr()
{
	SNode *right, *left;
	Token op_tok;
	if (cur_tok->getType() == token_type::tKEYWORD)
	{
		op_tok = cur_tok;
		advance();
		left = expr();
		if (left->data->getType() != token_type::tPLUS &&
			left->data->getType() != token_type::tMINUS &&
			left->data->getType() != token_type::tMUL &&
			left->data->getType() != token_type::tDIV &&
			left->data->getType() != token_type::tINT &&
			left->data->getType() != token_type::tFLOAT &&
			left->data->getType() != token_type::tENDL )
		{
            errors->parseErr();
			std::string x = "";
			errors->addErr(x + "Line: " + std::to_string(left->data->getPos().getLine()) + " column: " +
						   std::to_string(left->data->getPos().getCol()) + ". Expected an int, a float, '(' or a ';'.");
			return NULL;
		}
		left = crNodeChild(left, NULL, op_tok, op_tok.getPos());
        return left;
	}

	left = c_expr();
	while ( cur_tok->getType() == token_type::tKEYWORD &&
		   (cur_tok->getValueIdx() == get_keyword_id("AND") ||
			cur_tok->getValueIdx() == get_keyword_id("OR")))
	{
        op_tok = *cur_tok;
		advance();
		right = c_expr();
		left = crNodeChild(left, right, op_tok, op_tok.getPos());
	}

	return left;
}

SNode* Parser::c_expr()
{
    SNode *right, *left;
	Token op_tok;

	if (cur_tok->getType() == token_type::tKEYWORD &&
		cur_tok->getValueIdx() == get_keyword_id("NOT"))
	{
		op_tok = cur_tok;
		advance();
		left = crNodeChild(c_expr(), NULL, op_tok, op_tok.getPos());
		return left;
	}

	left = a_expr();
	while (cur_tok->getType() == token_type::tEQ ||
		   cur_tok->getType() == token_type::tLT||
		   cur_tok->getType() == token_type::tGT||
		   cur_tok->getType() == token_type::tLTE||
		   cur_tok->getType() == token_type::tGTE)
	{
		op_tok = *cur_tok;
		advance();
		right = a_expr();
		left = crNodeChild(left, right, op_tok, op_tok.getPos());
	}

	return left;
}

SNode* Parser::a_expr()
{
    SNode *right, *left;
	Token op_tok;

    left = term();
	while (cur_tok->getType() == token_type::tPLUS ||
		   cur_tok->getType() == token_type::tMINUS)
	{
		op_tok = *cur_tok;
		advance();
		right = term();
		left = crNodeChild(left, right, op_tok, op_tok.getPos());
	}

	return left;
}

SNode* Parser::parse()
{
	advance();

	SNode *res = expr();

	if (cur_tok->getType() != token_type::tEOF) {
		errors->parseErr();
		std::string x = "";
		errors->addErr(x + "Line: " + std::to_string(cur_tok->getPos().getLine()) + " column: " +
						   std::to_string(cur_tok->getPos().getCol()) + ". Expected '+', '-', '*' or '/'.");
	}

    return res;
}
