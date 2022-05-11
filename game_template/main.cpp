#include<Windows.h>
#include"game.h"

int WINAPI WinMain(
	[[maybe_unused]] _In_ HINSTANCE hInstance, 
	[[maybe_unused]] _In_opt_  HINSTANCE hPrevInstance, 
	[[maybe_unused]] _In_ LPSTR lpCmdLine, 
	[[maybe_unused]] _In_ int nShowCmd) 
{
	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	SetBackgroundColor(255, 255, 255);  //îwåiÇîíêFÇ…Ç∑ÇÈ
	SetWindowStyleMode(7);
	SetWindowSizeChangeEnableFlag(TRUE);

	if (DxLib_Init() == -1)return -1;
	Game game_controler;
	game_controler.init();
	while (ProcessMessage() == 0)
	{
		game_controler.update();
	}
	DxLib_End();
	return 0;
}