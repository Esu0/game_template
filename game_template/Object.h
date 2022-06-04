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
	int s_handle = -1;
	unsigned int width = 0;
	unsigned int height = 0;
public:
	Image()
	{}

	explicit Image(int _handle, int _s_handle, unsigned int _width, unsigned int _height) : handle(_handle), s_handle(_s_handle), width(_width), height(_height)
	{}

	friend class Sprite;
};

class ImageRegistry
{
private:
	static int* SoftImages;
	static int* Images;
	static size_t end;
	static size_t capacity;

private:
	static void init(size_t size)
	{
		delete_image();
		Images = new int[size];
		SoftImages = new int[size];
		if (Images == nullptr || SoftImages == nullptr)throw std::bad_alloc();
		for (size_t i = 0; i < size; ++i)Images[i] = -1;
		for (size_t i = 0; i < size; ++i)SoftImages[i] = -1;
		capacity = size;
		end = 0;
	}

	static void delete_memory()noexcept
	{
		if (Images != nullptr)delete[] Images;
		if (SoftImages != nullptr)delete[] SoftImages;
	}
public:

	[[nodiscard]]
	static Image push(const wchar_t *path)
	{
		if (end >= capacity)throw std::out_of_range("index out-of-range");
		SoftImages[end] = LoadSoftImage(path);
		Images[end] = CreateGraphFromSoftImage(SoftImages[end]);
		if (Images[end] == -1 || SoftImages[end] == -1)throw get_handle_failed();
		int x, y;
		GetGraphSize(Images[end], &x, &y);
		auto i = end++;
		return Image(Images[i], SoftImages[i], x, y);
	}

	static void delete_image()noexcept
	{
		if (Images != nullptr)
		{
			for (size_t i = 0; i < end; ++i)
			{
				DeleteGraph(Images[i]);
				Images[i] = -1;
				DeleteSoftImage(SoftImages[i]);
				SoftImages[i] = -1;
			}
		}
		end = 0;
	}


	friend class GlobalControl;
};

template<typename Ty>
concept imageTy = requires(Ty i)
{
	{ i.handle }->std::same_as<int>;
	{ i.width }->std::same_as<unsigned int>;
	{ i.height }->std::same_as<unsigned int>;
};

class Sprite
{
private:
	std::vector<int> handle;
	std::vector<int> s_handle;
	unsigned int width = 0;
	unsigned int height = 0;
public:
	Sprite(){}

	template<typename... Args>
	Sprite(const Args&... image): handle(), s_handle()
	{
		std::initializer_list<Image> images = { image... };
		handle.reserve(images.size());
		s_handle.reserve(images.size());
		for (auto i : images)
		{
			handle.push_back(i.handle);
			s_handle.push_back(i.s_handle);
			if (width < i.width)width = i.width;
			if (height < i.height)height = i.height;
		}
	}

	explicit Sprite(std::initializer_list<Image> images): handle(), s_handle()
	{
		handle.reserve(images.size());
		s_handle.reserve(images.size());
		for (auto i : images)
		{
			handle.push_back(i.handle);
			s_handle.push_back(i.s_handle);
			if (width < i.width)width = i.width;
			if (height < i.height)height = i.height;
		}
	}

	size_t image_num()
	{
		return handle.size();
	}

	void draw(size_t index, Vector2<float> pos)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraphF(pos.x, pos.y, 1.0, 0.0, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}

	void draw(size_t index, Vector2<float> pos, double angle)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraphF(pos.x, pos.y, 1.0, angle, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}

	void draw(size_t index, Vector2<float> pos, Vector2<double> scale, double angle)
	{
		if (index >= handle.size())return;
		if (DrawRotaGraph3F(pos.x, pos.y, 0.0, 0.0, scale.x, scale.y, angle, handle[index], TRUE))
			throw std::runtime_error("•`‰æŽ¸”s");
	}

	Vector2<int> GetSize()
	{
		return { (int)width,(int)height };
	}

	unsigned int Width()
	{
		return width;
	}

	unsigned int Height()
	{
		return height;
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

namespace objects
{
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

	class AnimationObject : public BasicConcreteObject
	{
	protected:
		unsigned int _anim_speed;
		bool _animation;
		unsigned int _frame;

	public:
		virtual void draw() override
		{
			reinterpret_cast<BasicConcreteObject*>(this)->draw();
			if (_animation)
			{
				if (_frame >= _anim_speed)
				{
					if (++_state >= _sprite.image_num())_state = 0;
					_frame = 1;
				}
				else
				{
					++_frame;
				}
			}
		}

		void anim_stop()
		{
			_animation = false;
		}
		void anim_start()
		{
			_animation = true;
			_state = 0;
			_frame = 0;
		}
		void anim_start(size_t state)
		{
			_animation = true;
			_state = state;
			_frame = 0;
		}
		void anim_restart()
		{
			_animation = true;
		}
	};

	class Physic
	{
	protected:
		Vector2<double> pos;//ˆÊ’u
		Vector2<double> vel;//‘¬“x
		Vector2<double> acc;//‰Á‘¬“x

	public:
		virtual void next()
		{
			pos += vel;
			vel += acc + GlobalGameSetting::gravity;
		}
	};
}
void GameExit();