#pragma once

#include <string>

class Lexer
{
public:
	static const int DIGIT_COUNT = 10;
	const char DIGITS[DIGIT_COUNT] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	const std::string ADD_COMMAND = "add";
	const std::string OUTPUT_COMMAND = "output";
	const std::string LOOP_START_COMMAND = "loop";
	const std::string LOOP_END_COMMAND = "endloop";
	static const char SEPARATOR = '_'; 

	std::string toTokens(std::string input);
	bool isNumber(std::string token);
	char KeywordToken(std::string token);

};

