#include "Interpreter_c.h"
#include "Token_type_strings.h"

Value* Interpreter::visit(SNode *node)
{
	if (node->data->getType() == token_type::tINT ||
		node->data->getType() == token_type::tFLOAT)
	{
		return visitNum(node);
	}else if (node->condition == NULL && node->right != NULL)
	{
		return visitBinOp(node);
	}else if (node->condition == NULL && node->right == NULL)
	{
		 return visitUnOp(node);
	}else
	{
		 return visitIfOp(node);
	}
}

Value* Interpreter::visitNum(SNode *node)
{
	Number *res = new Number(std::stof(node->data->getValue()), node->pos, errors);
	return res;
}

Value* Interpreter::visitIfOp(SNode *node)
{
	Value *cond = visit(node->condition);
	free(node->condition);

	if (((Number*)cond)->evaluate())
	{
		freeNode(node->right);
		delete(cond);
		return visit(node->left);
	}else
	{
		if (node->right)
		{
			freeNode(node->left);
			delete(cond);
			return visit(node->right);
		}else
		{
			freeNode(node);
			return cond;
		}
	}
}

Value* Interpreter::visitBinOp(SNode *node)
{
	Value* val1 = visit(node->left);
	if (errors->happened()){ delete(val1); freeNode(node); return NULL; }
	Value* val2;


	if (node->data->getType() == token_type::tPLUS)
	{
		val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		*((Number*)val1) = ((Number*)val1)->add_to(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMINUS)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		*((Number*)val1) = ((Number*)val1)->sub_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMUL)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		*((Number*)val1) = ((Number*)val1)->mul_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tDIV)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		*((Number*)val1) = ((Number*)val1)->div_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tEQ)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->eq_to(val2);
	}else if (node->data->getType() == token_type::tNEQ)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->eq_to(val2);
		val1 = val1->not_op();
	}else if (node->data->getType() == token_type::tLT)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->ls_then(val2);
	}else if (node->data->getType() == token_type::tGT)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->gr_then(val2);
	}else if (node->data->getType() == token_type::tLTE)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->lse_then(val2);
	}else if (node->data->getType() == token_type::tGTE)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->gre_then(val2);
	}else if (node->data->getType() == token_type::tKEYWORD &&
			  node->data->getValueIdx() == get_keyword_id("AND"))
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->and_op(val2);
	}else if (node->data->getType() == token_type::tKEYWORD &&
			  node->data->getValueIdx() == get_keyword_id("OR"))
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		val1 = val1->or_op(val2);
	}else if (node->data->getType() == token_type::tKEYWORD &&
			  node->data->getValueIdx() == get_keyword_id("while"))
	{
		while (val1->evaluate())
		{
            val2 = visit(node->right);
			if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }
		}
	}

	delete(val2);
	freeNode(node);
	if (errors->happened()){ delete(val1); return NULL; }

	return val1;
}

Value* Interpreter::visitUnOp(SNode *node)
{
	Value *val = visit(node->left);
	Value *act, *tmp;

	if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("NOT"))
	{
		val = val->not_op();
	}else if (node->data->getType() == token_type::tMINUS)
	{
		*((Number*)val) = ((Number*)val)->mul_by(Number(-1, val->getPos(), errors));
	}else if (node->data->getType() == token_type::tKEYWORD)
	{
		int is_keyword = 0;

		for (int i = 0; i < KEYWORD_COUNT; i++)
		{
			if (strcmp(node->data->getValue().c_str(), keywords[i]) == 0)
			{
				is_keyword = i;
				break;
			}
		}
		act = new Action(is_keyword,(int)(((Number*)val)->getVal()), val->getPos(), errors);
        tmp = val;
		val = act;
		delete(tmp);
	}

	freeNode(node);

	return val;
}

