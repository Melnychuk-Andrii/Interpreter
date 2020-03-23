#ifndef Interpreter_cH
#define Interpreter_cH

#include "Node.h"
#include "Number.h"
#include "Action.h"
#include "Error_class.h"

class Interpreter
{
private:
	SNode *root;
	Err *errors;

public:
	Interpreter(){}
	Interpreter(SNode *r, Err *er){root = r; errors = er;}
	Value* visit(SNode *node);
	Value* visitNum(SNode *node);
	Value* visitBinOp(SNode *node);
    Value* visitIfOp(SNode *node);
	Value* visitUnOp(SNode *node);

};

#endif
