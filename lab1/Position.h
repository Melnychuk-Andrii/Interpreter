#ifndef PositionH
#define PositionH

class Position
{
private:
	int idx, ln, col;

public:
	Position(){idx = 0; ln = 1; col = 1;};
	int getPos(){return idx;};
	int getLine(){return ln;};
	int getCol(){return col;};
    void advance(char cur);
};

#endif
