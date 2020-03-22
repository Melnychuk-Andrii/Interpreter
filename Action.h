#ifndef ActionH
#define ActionH

#include "Value.h"
#define ACTION_LIM 10000

class Action: public Value
{
private:
	int val[ACTION_LIM];
	int act[ACTION_LIM];
	int act_c;

public:
	Action():Value(Position(), NULL){}
	Action(int a, int x, Position p, Err *e):Value(p, e){act_c = 0; act[act_c++] = a; val[act_c - 1] = x;}

    std::string represent();
	double getVal(int x){return val[x];}
	double getAct(int x){return act[x];}
	void addAct(int x, int v);
	void addAct(int x);

};

#endif
