#pragma once

#include <string>

class Lexer
{
public:
	const char DIGITS[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	const std::string ADD_COMMAND = "add";
	const std::string OUTPUT_COMMAND = "output";
	const std::string LOOP_START_COMMAND = "loop";
	const std::string LOOP_END_COMMAND = "endloop";
	const std::string SEPARATOR = "_";

	std::string toTokens(std::string path);

private:
	const int DIGIT_COUNT = 10;

	bool isNumber(std::string token);
	bool isKeyword(std::string token);

};

