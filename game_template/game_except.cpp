#include"game_except.h"

void expect(int e)
{
	if (e != 0)
	{
		MessageBoxW(NULL, L"���炩�̃G���[", L"Error Info", MB_ICONERROR);
		std::exit(1);
	}
}