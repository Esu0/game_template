#include"game.h"


void Start::update()
{
	textobj.next();
	textobj2.next();
	textobj.SetText(std::to_wstring(CtrGlobal.GetFPSNow()));
	textobj2.SetText(std::to_wstring(t.remaining()));
	textobj.draw();
	textobj2.draw();
	DrawCircle({ 300,300 }, 120, 0x000000);
	DrawEllipse({ 640,320 }, 80, 300, 0x000000);
	//if (t.alert())SceneControler::TransScene<Start, Scene1>();
}

void Scene1::update()
{
	s.draw(0, { 500.0, 500.0 }, { 3.0,1.2 }, -DX_PI / 4);
	if (t.alert())GameExit();
}