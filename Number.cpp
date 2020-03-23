#include "Number.h"

std::string Number::represent()
{
	return std::to_string(val);
}

Number Number::add_to(Number x)
{
	return Number(val + x.getVal(), pos, errors);
}

Number Number::sub_by(Number x)
{
	return Number(val - x.getVal(), pos, errors);
}

Number Number::mul_by(Number x)
{
	return Number(val * x.getVal(), pos, errors);
}

Value* Number::eq_to(Value* x)
{
	if (((Number*)x)->getVal() == val)
		val = 1;
	else
		val = 0;
	return this;
}

int Number::evaluate()
{
	if (val > 0)
	{
		val = 1;
		return 1;
	}
	else
	{
		val = 0;
        return 0;
	}
}

Value* Number::gr_then(Value* x)
{
	if (((Number*)x)->getVal() < val)
		val = 1;
	else
		val = 0;
	return this;
}

Value* Number::ls_then(Value* x)
{
	if (((Number*)x)->getVal() > val)
		val = 1;
	else
		val = 0;
	return this;
}

Value* Number::not_op()
{
	if (val > 0)
		val = 0;
	else
		val = 1;
    return this;
}

Value* Number::gre_then(Value* x)
{
	if (((Number*)x)->getVal() <= val)
		val = 1;
	else
		val = 0;
	return this;
}

Value* Number::lse_then(Value* x)
{
	if (((Number*)x)->getVal() >= val)
		val = 1;
	else
		val = 0;
	return this;
}

Value* Number::and_op(Value* x)
{
	if (val > 0)
		if (((Number*)x)->getVal() > 0)
			val = 1;
		else
			val = 0;
	else
		val = 0;

	return this;
}

Value* Number::or_op(Value* x)
{
	if (val > 0)
		val = 1;
	else if (((Number*)x)->getVal() > 0)
		val = 1;
	else
		val = 0;

	return this;
}


Number Number::div_by(Number x)
{
	if (x.getVal() == 0.0) {
		errors->interpErr();
		std::string x = "";
		errors->addErr(x + "Line: " + std::to_string(pos.getLine()) + " column: " +
					   std::to_string(pos.getCol()) + ". Runtime Error: Division by 0.");
		return *this;
	}
	return Number(val / x.getVal(), pos, errors);
}
