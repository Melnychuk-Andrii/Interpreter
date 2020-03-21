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

};

#endif
