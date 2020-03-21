#include "Error_class.h"

std::string Err::printify()
{
	std::string res = "";

	for (int i = 0; i < msg_count; i++)
	{
		res += messages[i]+"\r\n\r\n";
	}

	return res;
}
