#include "Action.h"
#include "Token_type_strings.h"

void Action::addAct(int x, int v)
{
	act[act_c] = x;
	val[act_c++] = v;
}

void Action::addAct(int x)
{
	act[act_c] = x;
	val[act_c++] = 1;
}

std::string Action::represent()
{
	std::string res = "";

	for (int i = 0; i < act_c; i++)
	{
		res = res + keywords[act[i]] + "(" + std::to_string(val[i])+")\r\n";
	}
    return res;
}
