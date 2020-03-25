#ifndef Interpreter_cH
#define Interpreter_cH

#include "Node.h"
#include "Number.h"
#include "Action.h"
#include "Error_class.h"

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>

#define FUNC_LIM 10000
#define EVENT_LIM 10000

class Interpreter
{
private:
	SNode *root;
	Err *errors;
	SNode *functions[FUNC_LIM], *events[EVENT_LIM];
	int func_count, event_count;
	int size_x, size_y;
	int pos_x, pos_y, items_count, items_left;
	int orient;  //r - 0 clockwise ++
	int **grid;
	TImage *img;

public:
	Interpreter(){}
	Interpreter(SNode *r, Err *er, int s_x, int s_y, int **gr, int item_l, TImage *imgs){
				root = r; errors = er; func_count = 0; event_count = 0; pos_x = 0;
				pos_y = 0; items_count = 0; items_left = item_l; orient = 0;
				size_x = s_x; size_y = s_y; grid = gr; img = imgs;}
	Value* visit(SNode *node);
	Value* visitNum(SNode *node);
	Value* visitBinOp(SNode *node);
    Value* visitIfOp(SNode *node);
	Value* visitUnOp(SNode *node);
	Value* visitActionOp(SNode *node);
	Value* visitFuncCallOp(SNode *node);
	Value* visitFuncOp(SNode *node);
	Value* visitEventOp(SNode *node);
	Value* visitWhileOp(SNode *node);
	void eventChecker();
    void updateView();

};

#endif
