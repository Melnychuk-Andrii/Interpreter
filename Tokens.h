#ifndef TOKENS
#define TOKENS
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
	std::string printable();

};

#endif