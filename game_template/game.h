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
		//ÉOÉçÅ[ÉoÉãê›íËÇ»Ç«
		CtrGlobal.BackGroundColor(Color::hsv(100, 0.8, 0.5));
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

