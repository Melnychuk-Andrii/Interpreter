#ifndef TOKEN
#define TOKEN
#include <string>
#include "Token_types.h"

class Token
{
private:
	token_type type;
	std::string value;
	bool has_value;

public:
	Token(){};
	Token(token_type x, std::string y){type = x; value = y; has_value = 1;};
    Token(token_type x){type = x; has_value = 0;};
	Token(Token *x) { type = x->getType(); value = x->getValue(); has_value = x->valIs(); }
	std::string printable();
    token_type getType(){return type;}
	std::string getValue() { return value; }
	bool valIs() { return has_value; }
};

#endif
