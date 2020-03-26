#ifndef NodeH
#define NodeH

#include "Token.h"

#define MAX( x , y ) ((x)>(y)? (x):(y))

struct Node
{
	Token *data;
	Position pos;
	struct Node *left, *right, *father, *condition, *if_next;
};

typedef struct Node SNode;

char* printify(SNode *root);
SNode* createNode(Token *dat, Position p);
SNode* crNodeChild(SNode *datl, SNode *datr, Token operation, Position p);
SNode* crNodeChildren(SNode *datl, SNode *datr, SNode *next_ops, Token operation, Position p);
SNode* crIfNode(SNode *datl, SNode *datr, SNode *datc, SNode *if_n, Token operation, Position p);
void freeNode(SNode *node);

#endif
