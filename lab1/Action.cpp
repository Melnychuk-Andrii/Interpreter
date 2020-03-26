#include "Action.h"
#include "Token_type_strings.h"

std::string Action::represent()
{
	std::string res = "";
	res = res + keywords[act] + "(" + std::to_string(val)+")\r\n";
    return res;
}
