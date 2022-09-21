#pragma once
#include<DxLib.h>
#include"gLibrary.h"
#include<functional>

void DrawRec(Vector2<int> pos, Vector2<int> size, Color col);
void DrawEllipse(Vector2<int> pos, int a, int b, Color col);
void DrawCircle(Vector2<int> pos, int radius, Color col);
void DrawFunc(std::function<Vector2<float>(int)> _F, int tmin, int tmax, Color col);