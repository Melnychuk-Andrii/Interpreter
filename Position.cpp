#include "Position.h"

void Position::advance(char cur)
{
	idx++;
	col++;
	if (cur == '\n')
	{
		col = 0;
        ln++;
    }
}
