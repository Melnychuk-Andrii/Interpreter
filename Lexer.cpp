#include "Lexer.h"
#include "Token_type_strings.h"

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
		}else if ( (cur_char > 64 && cur_char < 91) ||
				   (cur_char > 96 && cur_char < 123) )
		{
			tokens[token_count++]=make_keyword_token();
            if (tokens[token_count-1].getValue() == "ERROR")
			{
				token_count--;
			}
		}else if (cur_char == '<')
		{
			tokens[token_count++]=make_less_token();
		}else if (cur_char == '>')
		{
			tokens[token_count++]=make_greater_token();
		}else if (cur_char == '!')
		{
			tokens[token_count++]=make_not_eq_token();
			if (tokens[token_count-1].getValue() == "ERROR")
			{
				token_count--;
			}
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
		}else if (cur_char == '=')
		{
			tokens[token_count++]=Token(token_type::tEQ, position);
			advance();
		}else if (cur_char == ';')
		{
			tokens[token_count++]=Token(token_type::tENDL, position);
			advance();
		}else if (cur_char == '(')
		{
			tokens[token_count++]=Token(token_type::tLPAR, position);
			advance();
		}else if (cur_char == ')')
		{
			tokens[token_count++]=Token(token_type::tRPAR, position);
			advance();
		}else if (cur_char == '{')
		{
			tokens[token_count++]=Token(token_type::tLPAR, position);
			advance();
		}else if (cur_char == '}')
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

Token Lexer::make_greater_token()
{
    advance();
	if (cur_char == '=')
	{
		advance();
		return Token(token_type::tGTE, position);
	}else
	{
		advance();
		return Token(token_type::tGT, position);
	}
}

Token Lexer::make_less_token()
{
    advance();
	if (cur_char == '=')
	{
		advance();
		return Token(token_type::tLTE, position);
	}else
	{
		advance();
		return Token(token_type::tLT, position);
	}
}

Token Lexer::make_not_eq_token()
{
	std::string token_in_str = "";

	advance();
	if (cur_char == '=')
	{
		advance();
		return Token(token_type::tNEQ, position);
	}else
	{
		errors->lexErr();
		errors->addErr("Line: " + std::to_string(position.getLine()) + " column: " +
						   std::to_string(position.getCol()) + ". Expected '=' after '!'.");
		advance();
		return Token(token_type::tNEQ, "ERROR", position);
	}
}

Token Lexer::make_keyword_token()
{
	std::string token_in_str = "";

	while ( cur_char != 0 &&
		   ((cur_char > 64 && cur_char < 91) ||
			(cur_char > 96 && cur_char < 123) ||
			cur_char == '_' ||
			(cur_char > 47 && cur_char < 58)))
	{
		token_in_str += cur_char;
		advance();
	}

	int is_keyword = 0;

	for (int i = 0; i < KEYWORD_COUNT; i++)
	{
		if (strcmp(token_in_str.c_str(), keywords[i]) == 0)
		{
			is_keyword = 1;
			break;
		}
	}

	if (is_keyword)
		return Token(token_type::tKEYWORD, token_in_str, position);
	else
	{
		for (int i = 0; i < token_count; ++i)
		{
			if (tokens[i].getType() == token_type::tIDENT &&
				tokens[i].getValue() == token_in_str)
			{
				if (tokens[token_count-1].getValue() == "EVENT" ||
					tokens[token_count-1].getValue() == "FUNCTION")
				{
					errors->lexErr();
					errors->addErr("Line: " + std::to_string(position.getLine()) + " column: " +
									std::to_string(position.getCol()) + ". Identifier '" +
									token_in_str + "' already defined.");
					return Token(token_type::tNEQ, "ERROR", position);
				}else
					return Token(token_type::tIDENT, token_in_str, position);
			}
		}
		if (tokens[token_count-1].getValue() == "EVENT")
		{
			return Token(token_type::tNEQ, "ERROR", position);
		}
		if (tokens[token_count-1].getValue() == "FUNCTION")
		{
			return Token(token_type::tIDENT, token_in_str, position);
		}
		errors->lexErr();
		errors->addErr("Line: " + std::to_string(position.getLine()) + " column: " +
					   std::to_string(position.getCol()) + ". Unknown identifier '" +
					   token_in_str + "'.");
		return Token();
	}
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
