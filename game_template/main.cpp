#include<Windows.h>
#include"game.h"
#include"global_config.h"

int WINAPI WinMain(
	[[maybe_unused]] _In_ HINSTANCE hInstance, 
	[[maybe_unused]] _In_opt_  HINSTANCE hPrevInstance, 
	[[maybe_unused]] _In_ LPSTR lpCmdLine, 
	[[maybe_unused]] _In_ int nShowCmd) 
{
	if (DxLib_Init() == -1)return -1;

	SetAlwaysRunFlag(TRUE);
	ChangeWindowMode(TRUE);
	SetGraphMode(1280, 720, 32);
	SetBackgroundColor(255, 255, 255);  //îwåiÇîíêFÇ…Ç∑ÇÈ
	SetWindowStyleMode(7);
	SetWindowSizeChangeEnableFlag(TRUE);

	
	Game game_controler;
	game_controler.init();
	while (ProcessMessage() == 0)
	{
		game_controler.update();
	}
	DxLib_End();
	return 0;
}