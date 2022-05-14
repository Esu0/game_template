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

	default_scene::settings();
	CtrGlobal.Apply();
	if (DxLib_Init() == -1)return -1;
	
	SceneControler::TransDefault<default_scene>();
	while (ProcessMessage() == 0)
	{
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		SceneControler::do_update();
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}