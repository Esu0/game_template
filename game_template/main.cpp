#include<Windows.h>
#include"game.h"
#include"global_config.h"

class private_ref
{
public:
	static void setfps(double current)
	{
		CtrGlobal.fpsnow = current;
	}
	static void nextframe()
	{
		++GlobalControl::frame;
	}
};

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
	long long nowtime, prevtime = 0;
	SceneControler::TransDefault<Start>();
	while (ProcessMessage() == 0 && Loop)
	{
		private_ref::nextframe();
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		SceneControler::do_update();
		ScreenFlip();
		nowtime = GetNowHiPerformanceCount();
		while (nowtime - prevtime <= (long long)(1000000.0 / CtrGlobal.GetFPS() + 0.5))
		{
			nowtime = GetNowHiPerformanceCount();
		}
		private_ref::setfps(1000000.0 / (nowtime - prevtime));
		prevtime = nowtime;
	}
	CtrGlobal.End();
	return 0;
}