#pragma once
#include<DxLib.h>
#include"game_except.h"

enum class sampling : char
{
	none,
	x4_4,
	x8_8,
	x16_16,
};

class Font
{
private:
	int handle;
	byte size = 0xff;
	byte thickness = 0xff;
	bool edge = false;
	bool antialias = false;
	sampling antialias_sampling = sampling::none;
	bool moved = false;

public:
	Font(const wchar_t* fontname)
	{
		if ((handle = CreateFontToHandle(fontname, -1, -1)) == -1)
		{
			throw get_handle_failed();
		}
	}

	Font(const wchar_t* fontname, byte _size, byte _thick, bool _edge = false) : size(_size), thickness(_thick), edge(_edge)
	{
		if ((handle = CreateFontToHandle(fontname, _size, _thick, edge ? DX_FONTTYPE_EDGE : -1)) == -1)
		{
			throw get_handle_failed();
		}
	}

	Font(const wchar_t* fontname, byte _size, byte _thick, bool _edge, sampling _samp) :
		size(_size),
		thickness(_thick),
		edge(_edge),
		antialias(true),
		antialias_sampling(_samp)
	{
		if ((handle = CreateFontToHandle(fontname, size, thickness, 10 * (int)antialias_sampling + (edge ? 3 : 2))) == -1)
		{
			throw get_handle_failed();
		}
	}

	static Font MakeNew(const wchar_t* fontname)
	{
		return Font(fontname);
	}

	static Font MakeNew(const wchar_t* fontname, byte _size, byte _thick)
	{
		return Font(fontname, _size, _thick);
	}

	static Font MakeNew(const wchar_t* fontname, byte _size, byte _thick, bool _edge)
	{
		return Font(fontname, _size, _thick);
	}

	static Font MakeNewAntialias(const wchar_t* fontname, byte _size, byte _thick, bool _edge, sampling _samp)
	{
		return Font(fontname, _size, _thick, _edge, _samp);
	}

	Font(const Font&) = delete;
	Font(Font&& _Right)noexcept:
		handle(_Right.handle),
		size(_Right.size),
		thickness(_Right.thickness),
		edge(_Right.edge),
		antialias(_Right.antialias),
		antialias_sampling(_Right.antialias_sampling)
	{
		_Right.moved = true;
	}

	Font& operator=(const Font&) = delete;
	Font& operator=(Font&& _Right)noexcept
	{
		if (!moved)
		{
			DeleteFontToHandle(handle);
		}
		handle = _Right.handle;
		size = _Right.size;
		thickness = _Right.thickness;
		edge = _Right.edge;
		antialias = _Right.antialias;
		antialias_sampling = _Right.antialias_sampling;
		_Right.moved = true;
	}

	virtual ~Font()
	{
		if (!moved)
		{
			DeleteFontToHandle(handle);
		}
	}
};