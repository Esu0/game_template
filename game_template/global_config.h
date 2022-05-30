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
	static double game_speed;
	static double fps;
	static double fpsnow;
	static unsigned long long frame;
public:
	void ScreenX(int x)
	{
		if (x > 0)scx = x;
	}
	void ScreenY(int y)
	{
		if (y > 0)scy = y;
	}
	void ScreenSize(Vector2<int> size)
	{
		scx = size.x;
		scy = size.y;
	}
	Vector2<int> GetScreenSize()
	{
		return { scx,scy };
	}
	void BackGroundColor(Color bgc)
	{
		bg = bgc;
	}
	void ImagesMax(unsigned int max)
	{
		images_max = max;
	}
	unsigned int GetImageMax()
	{
		return images_max;
	}
	void SetSpeed(double sp)
	{
		if (sp > 0)game_speed = sp;
	}
	double GetSpeed()
	{
		return game_speed;
	}
	void SetFPS(double _fps)
	{
		if (_fps >= 0)
		{
			fps = _fps;
		}
	}
	double GetFPS()
	{
		return fps;
	}
	double GetFPSNow()
	{
		return fpsnow;
	}
	unsigned long long GetFrame()
	{
		return frame;
	}
	void Apply();
	void End();
	~GlobalControl()noexcept
	{}

	friend class private_ref;
};

class GlobalGameSetting
{
public:
	static Vector2<double> gravity;
};
extern GlobalControl CtrGlobal;
