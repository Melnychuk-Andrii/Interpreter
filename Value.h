#ifndef ValueH
#define ValueH

#include "Position.h"
#include "Error_class.h"
#include <string>

class Value
{
protected:
	Position pos;
	Err *errors;

public:
	Value(Position p, Err *e){pos = p; errors = e;}
	Position getPos(){return pos;}
	virtual Value* not_op(){return new Value(pos, errors);}
	virtual std::string represent() { return ""; }
	virtual Value* eq_to(Value* x){return this;}
	virtual Value* gr_then(Value* x){return this;}
	virtual Value* ls_then(Value* x){return this;}
	virtual Value* gre_then(Value* x){return this;}
	virtual Value* lse_then(Value* x){return this;}
	virtual Value* and_op(Value* x){return this;}
	virtual Value* or_op(Value* x){return this;}
};

#endif
