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

int Token::getValueIdx()
{
	for (int i = 0; i < KEYWORD_COUNT; i++)
	{
		if (strcmp(value.c_str(), keywords[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}
