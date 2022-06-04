#include"Object.h"

char* SceneControler::ScenesPtr = nullptr;
std::function<void()> SceneControler::update;
bool Loop = true;

int* ImageRegistry::Images = nullptr;
int* ImageRegistry::SoftImages = nullptr;
size_t ImageRegistry::end = 0;
size_t ImageRegistry::capacity = 0;


void GameExit()
{
	Loop = false;
}