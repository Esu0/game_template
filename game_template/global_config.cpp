#include"global_config.h"
#include"Object.h"
int GlobalControl::scx = 1280;
int GlobalControl::scy = 720;
Color GlobalControl::bg = 0xffffff;
unsigned int GlobalControl::images_max = 65535;

void GlobalControl::Apply()
{
	expect(SetGraphMode(scx, scy, 32, 60));
	expect(SetBackgroundColor(bg.R, bg.G, bg.B, 255 - bg.A));
	ImageRegistry::init(images_max);
}

void GlobalControl::End()
{
	ImageRegistry::delete_image();
	ImageRegistry::delete_memory();
	if (DxLib_End() == -1)exit(1);
}

GlobalControl CtrGlobal;

Vector2<double> GlobalGameSetting::gravity;