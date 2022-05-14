#pragma once
#include"gLibrary.h"
#include"game_except.h"
#include<string>

class GlobalControl
{
private:
	static int scx, scy;
	static Color bg;

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
	void Apply()
	{
		expect(SetGraphMode(scx, scy, 32, 60));
		expect(SetBackgroundColor(bg.R, bg.G, bg.B, 255 - bg.A));
	}
	~GlobalControl()noexcept
	{}
};

extern GlobalControl CtrGlobal;
