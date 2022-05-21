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
#include"global_config.h"

class Image
{
private:
	int handle = -1;

public:
	Image()
	{}

	explicit Image(int _handle): handle(_handle)
	{}

	friend class Sprite;
};


class ImageRegistry
{
private:
	static int* Images;
	static size_t end;
	static size_t capacity;

private:
	static void init(size_t size)
	{
		delete_image();
		Images = new int[size];
		if (Images == nullptr)throw std::bad_alloc();
		for (size_t i = 0; i < size; ++i)Images[i] = -1;
		capacity = size;
		end = 0;
	}

	static void delete_memory()noexcept
	{
		if (Images != nullptr)delete[] Images;
	}
public:

	[[nodiscard]]
	static Image push(const wchar_t *path)
	{
		if (end >= capacity)throw std::out_of_range("index out-of-range");
		Images[end] = LoadGraph(path);
		std::wstring ws = std::to_wstring(Images[end]);
		if (Images[end] == -1)throw get_handle_failed();
		return Image(Images[end++]);
	}

	static void delete_image()noexcept
	{
		if (Images != nullptr)
		{
			for (size_t i = 0; i < end; ++i)
			{
				DeleteGraph(Images[i]);
			}
		}
		end = 0;
	}


	friend class GlobalControl;
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
			handle.push_back(i.handle);
		}
	}

	explicit Sprite(std::initializer_list<Image> images): handle()
	{
		handle.reserve(images.size());
		for (auto i : images)
		{
			handle.push_back(i.handle);
		}
	}

	size_t image_num()
	{
		return handle.size();
	}

	void draw(size_t index, Vector2<int> pos)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraph(pos.x, pos.y, 1.0, 0.0, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}
	
	void draw(size_t index, Vector2<double> pos)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraphF((float)pos.x, (float)pos.y, 1.0, 0.0, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}

	void draw(size_t index, Vector2<int> pos, double angle)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraph(pos.x, pos.y, 1.0, angle, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}

	void draw(size_t index, Vector2<float> pos, Vector2<double> scale, double angle)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraph3F(pos.x, pos.y, 0.0, 0.0, scale.x, scale.y, angle, handle[index], TRUE))
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
	void next()
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
		ImageRegistry::delete_image();
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

class BasicConcreteObject
{
protected:
	Vector2<double> pos;
	Sprite _sprite;
	size_t _state;

public:
	virtual void draw()
	{
		_sprite.draw(_state, pos);
	}

	virtual void next()
	{}

	virtual void set_sprite(size_t indice)
	{
		_state = indice;
	}
};
class Physic
{
private:
	Vector2<double> pos;//ˆÊ’u
	Vector2<double> vel;//‘¬“x
	Vector2<double> acc;//‰Á‘¬“x
	
public:
	void draw()
	{}
};
void GameExit();