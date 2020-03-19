#include <string>
#include "Tokens.h"

std::string Token::printable()
{
	if (has_value)
	{
		return std::string(std::string()+token_names[type]+":"+value);
	}else
	{
		return std::string(token_names[type]);
	}
}
