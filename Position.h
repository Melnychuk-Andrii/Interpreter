#ifndef PositionH
#define PositionH

class Position
{
private:
	int idx, ln, col;

public:
	Position(){idx = 0; ln = 0; col = 0;};
	int getPos(){return idx;};
	int getLine(){return ln;};
	int getCol(){return col;};
    void advance(char cur);
};

#endif
