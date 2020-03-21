#include "Interpreter_c.h"

Value* Interpreter::visit(SNode *node)
{
	if (node->data->getType() == token_type::tINT ||
		node->data->getType() == token_type::tFLOAT)
	{
		return visitNum(node);
	}else if (node->left && node->right)
	{
		return visitBinOp(node);
	}else
	{
         return visitUnOp(node);
	}
}

Value* Interpreter::visitNum(SNode *node)
{
	Number *res = new Number(std::stof(node->data->getValue()), node->pos, errors);
	return res;
}

Value* Interpreter::visitBinOp(SNode *node)
{
	Value* val1 = visit(node->left);
	if (errors->happened()){ delete(val1); freeNode(node); return NULL; }
	Value* val2 = visit(node->right);
	if (errors->happened()){ delete(val1); delete(val2); freeNode(node); return NULL; }


	if (node->data->getType() == token_type::tPLUS)
	{
		*((Number*)val1) = ((Number*)val1)->add_to(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMINUS)
	{
		*((Number*)val1) = ((Number*)val1)->sub_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMUL)
	{
		*((Number*)val1) = ((Number*)val1)->mul_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tDIV)
	{
		*((Number*)val1) = ((Number*)val1)->div_by(*((Number*)val2));
	}

	delete(val2);
	freeNode(node);
	if (errors->happened()){ delete(val1); return NULL; }

	return val1;
}

Value* Interpreter::visitUnOp(SNode *node)
{
	Value* val = visit(node->left);

	if (node->data->getType() == token_type::tMINUS)
	{
		*((Number*)val) = ((Number*)val)->mul_by(Number(-1, val->getPos(), errors));
	}

	freeNode(node);

	return val;
}

