#include "Lexer.h"
#include "Tokens.h"

bool Lexer::isNumber(std::string token) //Функция проверки токена на число
{
	if (token.length() == 0)
		return false;
	if (token.length() > 1 && token[0] == Lexer::DIGITS[0])
		return false;

	for (int i = 0; i < token.length(); i++)
	{
		bool isDigit = false;
		for (int j = 0; j < Lexer::DIGIT_COUNT; j++)
		{
			if (token[i] == Lexer::DIGITS[j])
			{
				isDigit = !isDigit;
				break;
			}
		}

		if (!isDigit)
			return false;
	}
	return true;
}

char Lexer::KeywordToken(std::string keyword)
{
	if (keyword == Lexer::ADD_COMMAND)
		return ADD_TOKEN;
	else if (keyword == Lexer::OUTPUT_COMMAND)
		return OUTPUT_TOKEN;
	else if (keyword == Lexer::LOOP_START_COMMAND)
		return LOOP_START_TOKEN;
	else if (keyword == Lexer::LOOP_END_COMMAND)
		return LOOP_END_TOKEN;
	else
		return ERROR_TOKEN;
}

std::string Lexer::toTokens(std::string input)
{
	std::string temp = "", result = "";
	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == Lexer::SEPARATOR)
		{
			result += Lexer::KeywordToken(temp);
			temp = "";
		}
		else
			temp += input[i];
	}

	if (Lexer::isNumber(temp))
		result += NUMBER_TOKEN + temp + NUMBER_TOKEN;
	else
		result += KeywordToken(temp);

	return result;
}
