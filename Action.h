#ifndef ActionH
#define ActionH

#include "Value.h"

class Action: public Value
{
private:
	int val;
	int act;
	int act_c;

public:
	Action():Value(Position(), NULL){}
	Action(int a, int x, Position p, Err *e):Value(p, e){act_c = 0; act = a; val = x;}

    std::string represent();
	int getVal(){return val;}
	double getAct(){return act;}
    void actInit(){}

};

#endif
