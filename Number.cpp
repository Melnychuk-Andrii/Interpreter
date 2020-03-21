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
