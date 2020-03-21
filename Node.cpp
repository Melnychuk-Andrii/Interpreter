#define _CRT_SECURE_NO_WARNINGS
#include "Node.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define END_LINE "\r\n"

SNode* createNode(Token *dat)
{
	SNode *nd = new SNode;

	nd->left = NULL;
	nd->right = NULL;
	nd->father = NULL;

	nd->data = new Token(dat);

	return nd;
}

SNode* crNodeChild(SNode *datl, SNode *datr, Token operation)
{
	SNode *base = createNode(&operation);

	base->left = datl;
	base->right = datr;

	if (datl) datl->father = base;
	if (datr) datr->father = base;

    return base;
}

int countLeft(SNode *root)
{
	if (root == NULL) {
		return 0;
	}

	return MAX(countLeft(root->left) + 1, countLeft(root->right) - 1);
}

int countRight(SNode *root)
{
    if (root == NULL) {
		return 0;
	}

	return MAX(countRight(root->right) + 1, countRight(root->left) - 1);
}

int depthRight(SNode *root);

int depthLeft(SNode *root)
{
	if (root == NULL) {
		return 0;
	}

	return MAX(depthLeft(root->left) + 1, depthRight(root->left) + 1);
}

int depthRight(SNode *root)
{
    if (root == NULL) {
		return 0;
	}

	return MAX(depthLeft(root->right) + 1, depthRight(root->right) + 1);
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

	int left_c = countLeft(root) - 1,
		right_c = countRight(root) - 1,
		left_d = depthLeft(root) - 1,
		right_d = depthRight(root) - 1;

	char *result = new char[1000000],
		 *prefix = new char[1000000],
		 *childPref = new char[1000000];

	result[0] = 0;
	prefix[0] = 0;
	childPref[0] = 0;

	print_rec(root, result, prefix, childPref);

	return result;
}
