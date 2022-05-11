#pragma once
#include<string>
#include<DxLib.h>
#include"game_except.h"
#include<stdlib.h>
#include<new>
#include<vector>
#include<concepts>

class Image
{
private:
	int handle = 0;

public:
	Image()
	{}

	explicit Image(const wchar_t * path): handle(DxLib::LoadGraph(path))
	{
		if (handle == -1)throw get_handle_failed();
	}

	int get_handle()
	{
		return handle;
	}

	~Image()
	{
		DeleteGraph(handle);
	}
};

class Sprite
{
private:
	std::vector<int> handle;

public:
	Sprite(){}

	template<typename... Args>
	Sprite(const Args&... image): handle()
	{
		std::initializer_list<Image> images = { image... };
		handle.reserve(images.size());
		for (auto i : images)
		{
			handle.push_back(i.get_handle());
		}
	}

	explicit Sprite(std::initializer_list<Image> images): handle()
	{
		handle.reserve(images.size());
		for (auto i : images)
		{
			handle.push_back(i.get_handle());
		}
	}


	void draw(size_t index, int x, int y)
	{
		if (index >= handle.size())return;
		DrawRotaGraph(x, y, 1.0, 0.0, handle[index], TRUE);
	}
};

/*
class Object
{
protected:
	double x = 0, y = 0;
	Sprite sprite;

public:
	virtual void draw()
	{
		sprite.draw(0, (int)x, (int)y);
	}
	virtual void next() = 0;
};
*/

template<typename Ty>
concept Object = requires(Ty& Ob)
{
	Ob.draw();
	Ob.next();
};

template<Object ObjTy>
class ObjectGroup
{
	std::vector<ObjTy> objects;

	template<typename... _Valty>
	void emplace(_Valty&&... _Val)
	{
		objects.emplace_back(_Val...);
	}

	void draw()
	{
		for (ObjTy& elem : objects)
		{
			elem.draw();
		}
	}
};