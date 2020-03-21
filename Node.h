#ifndef NodeH
#define NodeH

#include "Token.h"

#define MAX( x , y ) ((x)>(y)? (x):(y))

struct Node
{
	Token *data;
	Position pos;
	struct Node *left, *right, *father;
};

typedef struct Node SNode;

char* printify(SNode *root);
SNode* createNode(Token *dat, Position p);
SNode* crNodeChild(SNode *datl, SNode *datr, Token operation, Position p);
void freeNode(SNode *node);

#endif
