#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include "Compiler.h"
#include "Lexer.h"

int main(int argc, char* argv[])
{
	std::string path;
	if (argc < 2)
	{
		std::cout << "List of arguments cant be empty";
	}
	else
	{
		path = argv[1];
	}
	
	Compiler compiler = Compiler();
	Lexer lexer = Lexer();

	std::string compInput = "";
	std::string line;
	std::fstream input;
	input.open(path, std::ios::in);
	if (input.is_open())
	{
		while (std::getline(input, line))
		{
			compInput += lexer.toTokens(line);
		}
	}
	input.close();

	std::ofstream execute;
	execute.open("runnable\\a.asm");
	execute << compiler.compile(compInput);
	execute.close();

	ShellExecute(NULL, L"open", L"cmd.exe", L"/K spec\\nasm -f win32 runnable\\a.asm -o runnable\\a.obj", NULL, SW_HIDE);
	ShellExecute(NULL, L"open", L"cmd.exe", L"/K spec\\GoLink /entry:Start /console kernel32.dll user32.dll runnable\\a.obj", NULL, SW_HIDE);
	return 0;
}
