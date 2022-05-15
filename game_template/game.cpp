#include"game.h"

int Start::count = 0;
int Scene1::count = 0;

void Start::update()
{
	s1.draw(0, 0, 0);
	s2.draw(0, 0, 100);
	++count;
	if (count > 120)SceneControler::TransScene<Start, Scene1>();
}

void Scene1::update()
{
	s.draw(0, 500, 0);
	++count;
	if (count > 120)GameExit();
}