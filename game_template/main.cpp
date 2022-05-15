#include<Windows.h>
#include"game.h"
#include"global_config.h"


int WINAPI WinMain(
	[[maybe_unused]] _In_ HINSTANCE hInstance, 
	[[maybe_unused]] _In_opt_  HINSTANCE hPrevInstance, 
	[[maybe_unused]] _In_ LPSTR lpCmdLine, 
	[[maybe_unused]] _In_ int nShowCmd) 
{
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);
	SetWindowStyleMode(7);
	SetWindowSizeChangeEnableFlag(TRUE);

	Start::settings();
	CtrGlobal.Apply();
	if (DxLib_Init() == -1)return -1;
	
	SceneControler::TransDefault<Start>();
	while (ProcessMessage() == 0 && Loop)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		SceneControler::do_update();
		ScreenFlip();
	}
	CtrGlobal.End();
	return 0;
}