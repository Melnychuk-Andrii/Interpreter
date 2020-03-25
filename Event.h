#ifndef EventH
#define EventH

#include "Action.h"

#define EV_ACT_LIM 10000

class Event: public Value
{
private:
	Action act[EV_ACT_LIM];
	int act_c;

public:
	Event():Value(Position(), NULL){}
	Event(Action a, Position p, Err *e):Value(p, e){act_c = 0; act[act_c++] = a;}

	std::string represent();
	Action getAct(int x){return act[x];}
	void addAct(Action x);
};

#endif
