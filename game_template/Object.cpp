#include"Object.h"

char* SceneControler::ScenesPtr = nullptr;
std::function<void()> SceneControler::update;
bool Loop = true;

void GameExit()
{
	Loop = false;
}