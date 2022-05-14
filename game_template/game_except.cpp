#include"game_except.h"

void expect(int e)
{
	if (e != 0)
	{
		MessageBoxW(NULL, L"âΩÇÁÇ©ÇÃÉGÉâÅ[", L"Error Info", MB_ICONERROR);
		std::exit(1);
	}
}