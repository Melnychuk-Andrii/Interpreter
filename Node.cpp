#define _CRT_SECURE_NO_WARNINGS
#include "Node.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define END_LINE "\r\n"

void freeNode(SNode *node)
{
	if (node->father)
	{
		if (node == node->father->left)
		{
			node->father->left = NULL;
		}else if (node == node->father->right)
		{
			node->father->right = NULL;
		}
	}

	if (node->left)
	{
		freeNode(node->left);
	}

	if (node->right)
	{
		freeNode(node->right);
	}

    delete(node);
}

SNode* createNode(Token *dat, Position p)
{
	SNode *nd = new SNode;

	nd->left = NULL;
	nd->right = NULL;
	nd->father = NULL;

	nd->data = new Token(dat);
	nd->pos = p;

	return nd;
}

SNode* crNodeChild(SNode *datl, SNode *datr, Token operation, Position p)
{
	SNode *base = createNode(&operation, p);

	base->left = datl;
	base->right = datr;
    base->pos = p;

	if (datl) datl->father = base;
	if (datr) datr->father = base;

	return base;
}

char* strcat1(char *dest, const char *source)
{
	char *res = (char*)calloc(1, strlen(dest) + strlen(source) + 1);

	strcat(res, dest);
	strcat(res, source);

	return res;
}

void print_rec(SNode *root, char *res, char *prefix, char *childPref)
{
	strcat(res, prefix);
	strcat(res, root->data->printable().c_str());
	strcat(res, END_LINE);

	if (root->left && root->right) {
		print_rec(root->left, res, strcat1(childPref, ">------ "), strcat1(childPref, "|       "));
		print_rec(root->right, res, strcat1(childPref, ">------ "), strcat1(childPref, "|       "));
	}
	else if (root->left || root->right) {
		print_rec((root->left? root->left:root->right) , res, strcat1(childPref, ">------ "), strcat1(childPref, "        "));
	}
}

char* printify(SNode *root)
{
	if (root == NULL) return NULL;

	char *result = new char[1000000],
		 *prefix = new char[1000000],
		 *childPref = new char[1000000];

	result[0] = 0;
	prefix[0] = 0;
	childPref[0] = 0;

	print_rec(root, result, prefix, childPref);

	return result;
}
