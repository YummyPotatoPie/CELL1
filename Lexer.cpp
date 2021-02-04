#include <iostream>
#include <fstream>
#include "Lexer.h"

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
