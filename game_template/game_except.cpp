#include"game_except.h"

void expect(int e)
{
	if (e != 0)
	{
		MessageBoxW(NULL, L"何らかのエラー", L"Error Info", MB_ICONERROR);
		std::exit(1);
	}
}