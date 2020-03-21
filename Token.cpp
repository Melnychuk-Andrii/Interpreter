#include <string>
#include "Token.h"
#include "Token_type_strings.h"

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
