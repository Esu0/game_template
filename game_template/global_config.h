#pragma once
#include"gLibrary.h"
#include"game_except.h"
#include<string>

class GlobalControl
{
private:
	static int scx, scy;
	static Color bg;
	static unsigned int images_max;
public:
	void ScreenX(int x)
	{
		if (x > 0)scx = x;
	}
	void ScreenY(int y)
	{
		if (y > 0)scy = y;
	}
	void BackGroundColor(Color bgc)
	{
		bg = bgc;
	}
	void ImagesMax(unsigned int max)
	{
		images_max = max;
	}
	void Apply();
	void End();
	~GlobalControl()noexcept
	{}
};

extern GlobalControl CtrGlobal;
