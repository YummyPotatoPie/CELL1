#include <iostream>
#include "Compiler.h"
#include <windows.h>
#include <shellapi.h>

int main()
{
	ShellExecute(NULL, L"open", L"cmd.exe", L"/K nasm -f win32 ", NULL, SW_SHOWNORMAL);
}
