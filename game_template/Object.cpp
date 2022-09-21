#include"Object.h"

char* SceneControler::ScenesPtr = nullptr;
std::function<void()> SceneControler::update;
bool Loop = true;

int* ImageRegistry::Images = nullptr;
size_t ImageRegistry::end = 0;
size_t ImageRegistry::capacity = 0;


void GameExit()
{
	Loop = false;
}

void SetAlpha(byte alpha)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
}

void EndAlpha()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}