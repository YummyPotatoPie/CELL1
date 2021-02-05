#include <string>
#include "Compiler.h"
#include "Tokens.h"

enum States
{
	ADD,
	LOOP,
	ENDLOOP
};

std::string Compiler::compile(std::string tokens)
{
	States state;
	int loops = 0;
	bool errorFlag = false;
	std::string temp, result = "";
	//Обязательная часть программы
	result += "NULL equ 0\n";
	result += "STD_OUTPUT_HANDLE equ -11\n\n";
	result += "extern GetStdHandle\n";
	result += "extern WriteFile\n";
	result += "extern ExitProcess\n\n";
	result += "section .data\n";
	result += "\tcell db 0\n\n";
	result += "section .bss\n";
	result += "\tStdHandle resd 1\n";
	result += "\tWritten resd 1\n\n";
	result += "section .text\n";
	result += "global Start\n";
	result += "mod:\n";
	result += "\tcmp ebx, 0\n";
	result += "\tjl lower\n";
	result += "\tret\n";
	result += "lower:\n";
	result += "\tadd ebx, 128\n";
	result += "\tmov [cell], ebx\n";
	result += "\tret\n\n";
	result += "Start:\n";
	result += "\tpush STD_OUTPUT_HANDLE\n";
	result += "\tcall GetStdHandle\n";
	result += "\tmov dword [StdHandle], eax\n\n";

	for (int i = 0; i < tokens.length(); i++)
	{
		temp = "";
		if (tokens[i] == ERROR_TOKEN)
		{
			errorFlag = true;
			result += "\tpush NULL\n";
			result += "\tcall ExitProcess\n";
			break;
		}
		if (tokens[i] == OUTPUT_TOKEN)
		{
			result += "\tpush ecx\n\n";
			result += "\tpush NULL\n";
			result += "\tpush Written\n";
			result += "\tpush 1\n";
			result += "\tpush cell\n";
			result += "\tpush dword [StdHandle]\n";
			result += "\tcall WriteFile\n\n";
			result += "\tpop ecx\n\n";
		}
		if (tokens[i] == ADD_TOKEN)
		{
			result += "\tmov ebx, [cell]\n";
			state = ADD;
		}
		if (tokens[i] == LOOP_START_TOKEN)
		{
			state = LOOP;
		}
		if (tokens[i] == LOOP_END_TOKEN)
		{
			state = ENDLOOP;
		}
		if (tokens[i] == NUMBER_TOKEN)
		{
			i++;
			while (tokens[i] != NUMBER_TOKEN && i < tokens.length())
			{
				temp += tokens[i];
				i++;
			}

			if (state == ADD)
			{
				result += "\tadd ebx, " + temp + "\n";
				result += "\tmov [cell], ebx\n";
				result += "\tcall mod\n\n";
			}
			if (state == LOOP)
			{
				loops++;
				result += "\tmov ecx, " + temp + "\n";
				result += "lp" + std::to_string(loops) + ":\n";
				result += "\tpush ecx\n";
			}
			if (state == ENDLOOP)
			{
				result += "\tinc ecx\n";
				result += "\tcmp ecx, " + temp + "\n";
				result += "\tjle lp" + std::to_string(loops) + "\n";
				result += "\tpop ecx\n\n";
				loops--;
			}
		}
	}

	if (!errorFlag)
	{
		result += "\tpush NULL\n";
		result += "\tcall ExitProcess\n";
	}

	return result;
}