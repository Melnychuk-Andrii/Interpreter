#ifndef Error_classH
#define Error_classH

#include <string>
#include "Position.h"

#define MAX_MSG_COUNT 1000

class Err
{
private:
	std::string messages[MAX_MSG_COUNT];
	int msg_count;
	bool lex_err, parse_err, interp_err;

public:
	Err(){msg_count = 0; lex_err = 0; parse_err = 0; interp_err = 0;};
	void addErr(std::string msg){messages[msg_count++] = msg;}
	std::string printify();
    bool happened(){if (msg_count != 0) return 1; else return 0;}
	void parseErr(){parse_err = 1;}
	void lexErr(){lex_err = 1;}
    void interpErr(){interp_err = 1;}
};

#endif
