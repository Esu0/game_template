#pragma once
#include"Object.h"
#include<Dxlib.h>
#include"global_config.h"
#include"gLibrary.h"
#include"texts.h"
#include"Timer.h"

class Start
{
public:
	Image i;
	Sprite s1, s2;
	objects::Text textobj;
	objects::Text textobj2;
	Timer t;

	static void settings()
	{
		//ÉOÉçÅ[ÉoÉãê›íËÇ»Ç«
		CtrGlobal.BackGroundColor(Color::hsv(200, 1, 0.5));
	}

	void init()
	{
		i = ImageRegistry::push(L"./back.png");
		s1 = Sprite(i);
		s2 = s1;
		textobj = objects::Text(objects::Text::DefaultFont);
		textobj.SetMove([](Vector2<float>& p) {p = { 200.0f,100.0f }; });
		textobj.ChangeColor(Color::rgb(255, 0, 0, 125));
		textobj2 = objects::Text(objects::Text::DefaultFont);
		textobj2.SetPos({ 300,200 });
		textobj2.ChangeColor(Color::rgb(255, 0, 0));
		t.sets(2);
		t.start();
	}

	void update();

};

class Scene1
{
public:
	Image i;
	Sprite s;
	Timer t;
	
	void init()
	{
		
		i = ImageRegistry::push(L"./back.png");
		s = Sprite(i);
		t.sets(10);
		t.start();
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

