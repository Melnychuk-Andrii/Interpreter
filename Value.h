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
	virtual std::string represent() { return ""; }
};

#endif
