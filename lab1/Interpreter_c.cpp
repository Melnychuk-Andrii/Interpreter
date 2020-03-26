#include "Interpreter_c.h"
#include "Token_type_strings.h"

Value* Interpreter::visit(SNode *node)
{
	if (checkedEvents == 0)
	{
		checkedEvents = 1;
		findEvents(node);
	}

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
		 node->data->getValueIdx() == get_keyword_id("ITEMS_LEFT")||
		 node->data->getValueIdx() == get_keyword_id("isWallLeft")||
		 node->data->getValueIdx() == get_keyword_id("isWallRight")||
		 node->data->getValueIdx() == get_keyword_id("isWallFront")||
		 node->data->getValueIdx() == get_keyword_id("isFruit"))))
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

void Interpreter::findEvents(SNode *node)
{
	if (node == NULL)
	{
		return;
	}
    if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("EVENT"))
	{
		events[event_count++] = node;
	}
	findEvents(node->left);
	findEvents(node->right);
	findEvents(node->if_next);
}

void Interpreter::eventChecker()
{
	for (int i = 0; i < event_count; ++i)
	{
		if (visit(events[i]->left)->evaluate())
		{
			inEvent = 1;
			visit(events[i]->right);
            inEvent = 0;
		}
    }
}

Value* Interpreter::visitActionOp(SNode *node)
{
	if (inEvent == 0) eventChecker();
	int count = 0;

	if (node->left)
        count = ((Number*)visit(node->left))->getVal();
	else
		count = 1;

	for (int i = 0; i < count; ++i)
	{
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
		Sleep(200);
		updateView();
	}

	if (node->right == NULL)
	{
		return NULL;
	}
	return visit(node->right);
}

void Interpreter::drawEyes(int x, int y, TColor color, float border)
{
	img->Canvas->Brush->Color = color;
	img->Canvas->Pen->Color = color;
	if (orient == 0)
	{
		img->Canvas->Rectangle(sqrx * ( x + 1 ) - 1.7 * sqrx * border,
						   sqry * ( y + 1 ) - 2.1 * sqry * border,
						   sqrx * ( x + 1 ) - 1 * sqrx * border,
						   sqry * ( y + 1 ) - 1.2 * sqry * border);

		img->Canvas->Rectangle(sqrx * ( x + 1 ) - 1.7 * sqrx * border,
						   sqry * ( y + 1 ) - 3.7 * sqry * border,
						   sqrx * ( x + 1 ) - 1 * sqrx * border,
						   sqry * ( y + 1 ) - 2.8 * sqry * border);
	}else if (orient == 2)
	{
		img->Canvas->Rectangle(sqrx * ( x + 1 ) - 3.8 * sqrx * border,
						   sqry * ( y + 1 ) - 2.1 * sqry * border,
						   sqrx * ( x + 1 ) - 3.1 * sqrx * border,
						   sqry * ( y + 1 ) - 1.2 * sqry * border);

		img->Canvas->Rectangle(sqrx * ( x + 1 ) - 3.8 * sqrx * border,
						   sqry * ( y + 1 ) - 3.7 * sqry * border,
						   sqrx * ( x + 1 ) - 3.1 * sqrx * border,
						   sqry * ( y + 1 ) - 2.8 * sqry * border);
	}else if (orient == 3)
	{
		img->Canvas->Rectangle(sqry * ( x + 1 ) - 2.1 * sqry * border,
							sqrx * ( y + 1 ) - 3.8 * sqrx * border,
							sqry * ( x + 1 ) - 1.2 * sqry * border,
							sqrx * ( y + 1 ) - 3.1 * sqrx * border);

		img->Canvas->Rectangle(sqry * ( x + 1 ) - 3.7 * sqry * border,
							sqrx * ( y + 1 ) - 3.8 * sqrx * border,
							sqry * ( x + 1 ) - 2.8 * sqry * border,
							sqrx * ( y + 1 ) - 3.1 * sqrx * border);
	}else
	{
		img->Canvas->Rectangle(sqry * ( x + 1 ) - 2.1 * sqry * border,
							sqrx * ( y + 1 ) - 2.2 * sqrx * border,
							sqry * ( x + 1 ) - 1.2 * sqry * border,
							sqrx * ( y + 1 ) - 1.5 * sqrx * border);

		img->Canvas->Rectangle(sqry * ( x + 1 ) - 3.7 * sqry * border,
							sqrx * ( y + 1 ) - 2.2 * sqrx * border,
							sqry * ( x + 1 ) - 2.8 * sqry * border,
							sqrx * ( y + 1 ) - 1.5 * sqrx * border);
    }
}

void Interpreter::drawSqr(int x, int y, TColor color, float border)
{
	img->Canvas->Brush->Color = color;
	img->Canvas->Pen->Color = color;
	img->Canvas->Rectangle(sqrx * x + sqrx * border, sqry * y + sqry * border,
						   sqrx * ( x + 1 ) - sqrx * border,
						   sqry * ( y + 1 ) - sqry * border);
}

void Interpreter::updateView()
{
	img->Canvas->Brush->Color = clBtnFace;
	img->Canvas->FillRect ( img->Canvas->ClipRect );

	for (int i = 0; i < size_x; ++i)
	{
		for (int j = 0; j < size_y; ++j)
		{
			if(grid[i][j] == -1)
			{
				drawSqr(i, j, clMedGray, 0);
			}else if(grid[i][j] >= 0)
			{
				drawSqr(i, j, clGreen, 0);
				if(grid[i][j] == 1)
				{
					drawSqr(i, j, clYellow, 0.3);
				}
			}
			if (pos_x == i && pos_y == j)
			{
				drawSqr(i, j, clAqua, 0.2);
				drawEyes(i, j, clNavy, 0.2);
			}
		}
	}
	img->Repaint();
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
	visit(functions[index]->left);
    return visit(node->right);
}

Value* Interpreter::visitFuncOp(SNode *node)
{
	functions[func_count++] = node;
	return visit(node->if_next);
}

Value* Interpreter::visitEventOp(SNode *node)
{
	return visit(node->if_next);
}

Value* Interpreter::visitWhileOp(SNode *node)
{
	Value *res = visit(node->left);
	while (((Number*)res)->evaluate())
	{
		visit(node->right);
		if (errors->happened()){ return NULL; }
        res = visit(node->left);
	}
    res = visit(node->if_next);
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
	else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("isWallLeft"))
	{
		int result;
		if (orient == 0)
		{
			if (pos_y > 0)
				result = (grid[pos_x][pos_y - 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 1)
		{
			if (pos_x < size_x - 1)
				result = (grid[pos_x + 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 2)
		{
			if (pos_y < size_y - 1)
				result = (grid[pos_x][pos_y + 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 3)
		{
			if (pos_x > 0)
				result = (grid[pos_x - 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}
		res = new Number(result, node->pos, errors);
	}else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("isWallRight"))
	{
		int result;
		if (orient == 2)
		{
			if (pos_y > 0)
				result = (grid[pos_x][pos_y - 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 3)
		{
			if (pos_x < size_x - 1)
				result = (grid[pos_x + 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 0)
		{
			if (pos_y < size_y - 1)
				result = (grid[pos_x][pos_y + 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 1)
		{
			if (pos_x > 0)
				result = (grid[pos_x - 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}
		res = new Number(result, node->pos, errors);
	}else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("isWallFront"))
	{
		int result;
		if (orient == 3)
		{
			if (pos_y > 0)
				result = (grid[pos_x][pos_y - 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 0)
		{
			if (pos_x < size_x - 1)
				result = (grid[pos_x + 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 1)
		{
			if (pos_y < size_y - 1)
				result = (grid[pos_x][pos_y + 1] == -1 ? 1:0);
			else
				result = 1;
		}else if (orient == 2)
		{
			if (pos_x > 0)
				result = (grid[pos_x - 1][pos_y] == -1 ? 1:0);
			else
				result = 1;
		}
		res = new Number(result, node->pos, errors);
	}else  if (node->data->getType() == token_type::tKEYWORD &&
		node->data->getValueIdx() == get_keyword_id("isFruit"))
	{
		res = new Number((grid[pos_x][pos_y] == 1 ? 1:0), node->pos, errors);
	}else
	{
	res = new Number(std::stof(node->data->getValue()), node->pos, errors);

	}
	return res;
}

Value* Interpreter::visitIfOp(SNode *node)
{
	Value *cond = visit(node->condition), *res;

	if (((Number*)cond)->evaluate())
	{
		delete(cond);
		res = visit(node->left);
		res = visit(node->if_next);
		return res;
	}else
	{
		if (node->right)
		{
			delete(cond);
			res = visit(node->right);
            res = visit(node->if_next);
			return res;
		}else
		{
			res = visit(node->if_next);
			return res;
		}
	}
}

Value* Interpreter::visitBinOp(SNode *node)
{
	Value* val1 = visit(node->left);
	if (errors->happened()){ delete(val1); return NULL; }
	Value* val2 = NULL;


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
