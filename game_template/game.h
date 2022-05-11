#pragma once
#include"Object.h"
#include<Dxlib.h>

class Game
{
public:
	Image i;
	Sprite s1, s2;
	void init()
	{
		i = Image(L"./back.png");
		s1 = Sprite(i);
		s2 = s1;
	}

	void update()
	{
		s1.draw(0, 0, 0);
		s2.draw(0, 0, 100);
	}
};