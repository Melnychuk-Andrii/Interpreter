#ifndef TOKEN
#define TOKEN
#include <string>
#include "Token_types.h"
#include "Position.h"

class Token
{
private:
	token_type type;
	std::string value;
	bool has_value;
    Position pos;

public:
	Token(){};
	Token(token_type x, std::string y, Position p){type = x; value = y; has_value = 1;pos = p;};
	Token(token_type x, Position p){type = x; has_value = 0; pos = p;};
	Token(Token *x) { type = x->getType(); value = x->getValue(); has_value = x->valIs(); pos = x->pos;}
	std::string printable();
    token_type getType(){return type;}
	std::string getValue() { return value; }
	int getValueIdx();
	bool valIs() { return has_value; }
	Position getPos(){return pos;}
};

#endif
