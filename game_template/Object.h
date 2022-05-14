#pragma once
#include<string>
#include<DxLib.h>
#include"game_except.h"
#include<stdlib.h>
#include<new>
#include<vector>
#include<concepts>
#include<stdexcept>
#include<functional>


class Image
{
private:
	int handle = -1;

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
};


class ImageRegistry
{
	
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
		if (DrawRotaGraph(x, y, 1.0, 0.0, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
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

template<typename Ty>
concept Scene = requires(Ty Sc)
{
	Sc.init();
	Sc.update();
};

template<Scene ScTy>
std::allocator<ScTy> alloc;

class SceneControler
{
	static char* ScenesPtr;
	static std::function<void()> update;

public:
	template<Scene ScDef>
	static void TransDefault()
	{
		ScenesPtr = reinterpret_cast<char*>(alloc<ScDef>.allocate(1));
		std::allocator_traits<std::allocator<ScDef>>::construct(alloc<ScDef>, reinterpret_cast<ScDef*>(ScenesPtr));
		update = [] { reinterpret_cast<ScDef*>(ScenesPtr)->update(); };
		reinterpret_cast<ScDef*>(ScenesPtr)->init();
	}

	template<Scene ScFrom, Scene ScTo>
	static void TransScene()
	{
		using allocf = std::allocator<ScFrom>;
		using traitsf = std::allocator_traits<allocf>;
		using alloct = std::allocator<ScTo>;
		using traitst = std::allocator_traits<alloct>;
		traitsf::destroy(alloc<ScFrom>, reinterpret_cast<ScFrom*>(ScenesPtr));
		alloc<ScFrom>.deallocate(reinterpret_cast<ScFrom*>(ScenesPtr), 1);
		ScenesPtr = reinterpret_cast<char*>(alloc<ScTo>.allocate(1));
		traitst::construct(alloc<ScTo>, reinterpret_cast<ScTo*>(ScenesPtr));
		update = [] { reinterpret_cast<ScTo*>(ScenesPtr)->update(); };
		reinterpret_cast<ScTo*>(ScenesPtr)->init();
	}

	static void do_update()
	{
		update();
	}
};

extern bool Loop;

void GameExit();