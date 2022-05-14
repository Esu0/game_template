#pragma once
#include"Object.h"
#include<Dxlib.h>
#include"global_config.h"
#include"gLibrary.h"

class default_scene
{
public:
	Image i;
	Sprite s1, s2;
	static int count;
	static void settings()
	{
		//グローバル設定など
		CtrGlobal.BackGroundColor(Color::hsv(200, 1, 0.5));
	}

	void init()
	{
		i = Image(L"./back.png");
		s1 = Sprite(i);
		s2 = s1;
	}

	void update();

};

class Scene1
{
public:
	Image i;
	Sprite s;
	static int count;
	void init()
	{
		i = Image(L"./back.png");
		s = Sprite(i);
	}

	void update();

};

class Scene2
{
public:
	void init()
	{

	}

	void update()
	{

	}
};

