#include "Lexer.h"

void Lexer::advance()
{
	position.advance(cur_char);
	if (position.getPos() < text.length())
	{
		cur_char = text[position.getPos()];
	}else
	{
		cur_char = 0;
	}
}

void Lexer::make_tokens()
{
	cur_char = text[position.getPos()];

	while(cur_char != 0)
	{
		if (strchr(DELIM, cur_char))
		{
			advance();
		}else if (strchr(DIGITS, cur_char) || cur_char == '.')
		{
			tokens[token_count++]=make_number_token();
		}else if (cur_char == '+')
		{
			tokens[token_count++]=Token(token_type::tPLUS, position);
			advance();
		}else if (cur_char == '-')
		{
			tokens[token_count++]=Token(token_type::tMINUS, position);
			advance();
		}else if (cur_char == '*')
		{
			tokens[token_count++]=Token(token_type::tMUL, position);
			advance();
		}else if (cur_char == '/')
		{
			tokens[token_count++]=Token(token_type::tDIV, position);
			advance();
		}else if (cur_char == '(')
		{
			tokens[token_count++]=Token(token_type::tLPAR, position);
			advance();
		}else if (cur_char == ')')
		{
			tokens[token_count++]=Token(token_type::tRPAR, position);
			advance();
		}else
		{
			errors->lexErr();
			errors->addErr("Line: " + std::to_string(position.getLine()) + " column: " +
						   std::to_string(position.getCol()) + ". Unexpected symbol '" +
						   cur_char + "'.");
            advance();
		}
	}
	tokens[token_count++]=Token(token_type::tEOF, position);
}

Token Lexer::make_number_token()
{
	std::string num_in_str = "";
	int dot_count = 0;

	while (cur_char != 0 && (strchr(DIGITS, cur_char) || cur_char == '.'))
	{
		if (cur_char == '.')
		{
			if (dot_count == 1) {
				break;
			}
			dot_count++;
			num_in_str += cur_char;
			advance();
		}else
		{
			num_in_str += cur_char;
			advance();
		}
	}

	if (dot_count == 0)
	{
		return Token(token_type::tINT, num_in_str, position);
	}else
	{
		return Token(token_type::tFLOAT, num_in_str, position);
	}

}

std::string Lexer::print_tokens()
{
	std::string result = "[";
	for (int i = 0; i < token_count - 1; ++i) {
		result += tokens[i].printable();
		result += ", ";
	}
	result += tokens[token_count - 1].printable();
	result += "]";
    return result;
}

Token* Lexer::returnTokens()
{
    return tokens;
}
