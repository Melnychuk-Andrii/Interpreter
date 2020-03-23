#ifndef NumberH
#define NumberH

#include "Value.h"

class Number: public Value
{
private:
	double val;

public:
	Number():Value(Position(), NULL){}
	Number(double x, Position p, Err *e):Value(p, e){val = x;}

    std::string represent();
    double getVal(){return val;}
	Number add_to(Number x);
	Number sub_by(Number x);
	Number mul_by(Number x);
	Number div_by(Number x);
	Value* not_op();
    int evaluate();
	Value* eq_to(Value* x);
	Value* gr_then(Value* x);
	Value* ls_then(Value* x);
	Value* gre_then(Value* x);
	Value* lse_then(Value* x);
	Value* and_op(Value* x);
	Value* or_op(Value* x);

};

#endif
