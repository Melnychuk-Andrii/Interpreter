#include "Interpreter_c.h"
#include "Token_type_strings.h"

Value* Interpreter::visit(SNode *node)
{
	if (node == NULL) 
	{
		return new Number(1, Position(), errors);
	}
	if (node->data->getType() == token_type::tINT ||
		node->data->getType() == token_type::tFLOAT ||
		(node->data->getType() == token_type::tKEYWORD &&
		(node->data->getValueIdx() == get_keyword_id("POS_X") ||
		 node->data->getValueIdx() == get_keyword_id("POS_Y") ||
		 node->data->getValueIdx() == get_keyword_id("ITEM_COUNT") ||
		 node->data->getValueIdx() == get_keyword_id("ITEMS_LEFT"))))
	{
		return visitNum(node);
	}else if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("if"))
	{
		return visitIfOp(node);
	}else if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("while"))
	{
		return visitWhileOp(node);
	}else if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("EVENT"))
	{
		return visitEventOp(node);
	}else if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("FUNCTION"))
	{
		return visitFuncOp(node);
	}else if (node->data->getType() == token_type::tIDENT)
	{
		return visitFuncCallOp(node);
	}else if (node->data->getType() == token_type::tKEYWORD &&
		(node->data->getValueIdx() == get_keyword_id("move") ||
		 node->data->getValueIdx() == get_keyword_id("turnleft") ||
		 node->data->getValueIdx() == get_keyword_id("turnright") ||
		 node->data->getValueIdx() == get_keyword_id("place") ||
		 node->data->getValueIdx() == get_keyword_id("collect")))
	{
		 return visitActionOp(node);
	}else if (node->right != NULL)
	{
		return visitBinOp(node);
	}else if (node->right == NULL)
	{
		 return visitUnOp(node);
	}
	return new Number(1, Position(), errors);
}

void Interpreter::eventChecker()
{
	for (int i = 0; i < event_count; ++i)
	{
		if (visit(events[i]->left)->evaluate())
		{
			visit(events[i]->right);
		}
    }
}

Value* Interpreter::visitActionOp(SNode *node)
{
	eventChecker();
	if (node->data->getValueIdx() == get_keyword_id("move"))
	{
		if (orient == 0)
		{
			pos_x ++;
			if (pos_x >= size_x)
			{
				pos_x = size_x - 1;
			}else if (grid[pos_x][pos_y] < 0)
			{
			   pos_x--;
			}
		}else if (orient == 2)
		{
			pos_x --;
			if (pos_x < 0)
			{
				pos_x = 0;
			}else if (grid[pos_x][pos_y] < 0)
			{
			   pos_x++;
			}
		}else if (orient == 1)
		{
			pos_y ++;
			if (pos_y >= size_y)
			{
				pos_y = size_y - 1;
			}else if (grid[pos_x][pos_y] < 0)
			{
			   pos_y--;
			}
		}else if (orient == 3)
		{
			pos_y --;
			if (pos_y < 0)
			{
				pos_y = 0;
			}else if (grid[pos_x][pos_y] < 0)
			{
			   pos_y++;
			}
		}
	}else if (node->data->getValueIdx() == get_keyword_id("turnleft"))
	{
	   orient--;
	   if (orient < 0)
	   {
		   orient = 3;
	   }
	}else if (node->data->getValueIdx() == get_keyword_id("turnright"))
	{
	   orient++;
	   if (orient > 3)
	   {
		   orient = 0;
	   }
	}else if (node->data->getValueIdx() == get_keyword_id("collect"))
	{
	   if (grid[pos_x][pos_y] > 0)
	   {
		  grid[pos_x][pos_y]--;
		  items_count++;
		  items_left--;
	   }
	}else if (node->data->getValueIdx() == get_keyword_id("place"))
	{
	   if (items_count > 0)
	   {
		  grid[pos_x][pos_y]++;
		  items_count--;
		  items_left++;
	   }
	}

	updateView();

	if (node->right == NULL)
	{
		return NULL;
	}
	return visit(node->right);
}

void Interpreter::updateView()
{

}

Value* Interpreter::visitFuncCallOp(SNode *node)
{
	int index = -1;
	for (int i = 0; i < func_count; ++i)
	{
		 if (functions[i]->right->data->getValue() == node->data->getValue())
		 {
			index = i;
			break;
		 }
	}
	if (index == -1)
	{
         return NULL;
	}
	return visit(functions[index]->left);
}

Value* Interpreter::visitFuncOp(SNode *node)
{
	functions[func_count++] = node;
	return new Number(1, Position(), errors);
}

Value* Interpreter::visitEventOp(SNode *node)
{
	events[event_count++] = node;
	return new Number(1, Position(), errors);
}

Value* Interpreter::visitWhileOp(SNode *node)
{
	Value *res;
	while (res->evaluate())
	{
		visit(node->right);
		if (errors->happened()){ return NULL; }
        res = visit(node->left);
	}
    return res;
}

Value* Interpreter::visitNum(SNode *node)
{
	Number *res;
	if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("POS_X"))
	{
		res = new Number(pos_x, node->pos, errors);
	}
	else if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("POS_Y"))
	{
		res = new Number(pos_y, node->pos, errors);
	}
	else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("ITEM_COUNT"))
	{
		res = new Number(items_count, node->pos, errors);
	}
	else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("ITEMS_LEFT"))
	{
		res = new Number(items_left, node->pos, errors);
	}
	else
	{
	res = new Number(std::stof(node->data->getValue()), node->pos, errors);

	}
	return res;
}

Value* Interpreter::visitIfOp(SNode *node)
{
	Value *cond = visit(node->condition), *res;
	free(node->condition);

	if (((Number*)cond)->evaluate())
	{
		delete(cond);
		res = visit(node->left);
		return res;
	}else
	{
		if (node->right)
		{
			delete(cond);
			res = visit(node->right);
			return res;
		}else
		{
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
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		*((Number*)val1) = ((Number*)val1)->add_to(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMINUS)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		*((Number*)val1) = ((Number*)val1)->sub_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tMUL)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		*((Number*)val1) = ((Number*)val1)->mul_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tDIV)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		*((Number*)val1) = ((Number*)val1)->div_by(*((Number*)val2));
	}else if (node->data->getType() == token_type::tEQ)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->eq_to(val2);
	}else if (node->data->getType() == token_type::tNEQ)
	{
		val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->eq_to(val2);
		val1 = val1->not_op();
	}else if (node->data->getType() == token_type::tLT)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->ls_then(val2);
	}else if (node->data->getType() == token_type::tGT)
	{
		val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->gr_then(val2);
	}else if (node->data->getType() == token_type::tLTE)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->lse_then(val2);
	}else if (node->data->getType() == token_type::tGTE)
	{
        val2 = visit(node->right);
		if (errors->happened()){ delete(val1); delete(val2); return NULL; }
		val1 = val1->gre_then(val2);
	}else if (node->data->getType() == token_type::tKEYWORD &&
			  node->data->getValueIdx() == get_keyword_id("AND"))
	{
		if (val1->evaluate()) {
			val2 = visit(node->right);
			if (errors->happened()){ delete(val1); delete(val2); return NULL; }
			val1 = val1->and_op(val2);
			delete(val2);
		}
	}else if (node->data->getType() == token_type::tKEYWORD &&
			  node->data->getValueIdx() == get_keyword_id("OR"))
	{
		if (!val1->evaluate()) {
			val2 = visit(node->right);
			if (errors->happened()){ delete(val1); delete(val2); return NULL; }
			if (val2->evaluate())
				val1 = val1->or_op(val2);
			delete(val2);
		}
		if (errors->happened()){ delete(val1); return NULL; }

		return val1;
	}

	delete(val2);
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

	}

	return val;
}
