#pragma once
#include"gLibrary.h"

class Global_control
{
private:
	int scx = 1280, scy = 720;
	Color bg = 0xffffff;

public:
	void ScreenX(int x)
	{
		scx = x;
	}
	void ScreenY(int y)
	{
		scy = y;
	}
	void BackGroundColor(Color bgc)
	{
		bg = bgc;
	}
	~Global_control()noexcept
	{}
};

extern Global_control CtrGlobal;