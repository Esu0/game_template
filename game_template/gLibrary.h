#pragma once
#include<cmath>
#include<concepts>
#include<DxLib.h>

/// <summary>
/// 色とアルファ値を表す型
/// </summary>
class Color
{
	using byte = unsigned char;
	Color(byte _R, byte _G, byte _B, byte _A)
		:R(_R), G(_G), B(_B), A(_A)
	{}

public:
	byte R = 0, G = 0, B = 0, A = 255;

	Color()
	{}

	Color(unsigned int _code)
		:R((_code >> 4) & 0xff), G((_code >> 2) & 0xff), B(_code & 0xff)
	{}

	/// <summary>
	/// RGB(A)値から色を生成
	/// </summary>
	/// <param name="_R">R値</param>
	/// <param name="_G">G値</param>
	/// <param name="_B">B値</param>
	/// <param name="_A">アルファ値</param>
	/// <returns>Color型に変換した結果</returns>
	static Color rgb(byte _R, byte _G, byte _B, byte _A = 255)
	{
		return Color(_R, _G, _B, _A);
	}
	
	//0 <= hue < 360, 0 <= sat <= 1, 0 <= val <= 1
	
	/// <summary>
	/// HSV値から色を生成
	/// </summary>
	/// <param name="hue">色相</param>
	/// <param name="sat">彩度</param>
	/// <param name="val">明度</param>
	/// <param name="_A">アルファ値</param>
	/// <returns>Color型に変換した結果</returns>
	static Color hsv(int hue, double sat, double val, byte _A = 255)
	{
		double max = val * 255;
		double min = (1.0 - sat) * max;
		if (0 <= hue && hue < 60)return Color((byte)max, (byte)((double)hue / 60 * (max - min) + min), (byte)min, _A);
		else if (hue < 120)return Color((byte)((double)(120 - hue) / 60 * (max - min) + min), (byte)max, (byte)min, _A);
		else if (hue < 180)return Color((byte)min, (byte)max, (byte)((double)(hue - 120) / 60 * (max - min) + min), _A);
		else if (hue < 240)return Color((byte)min, (byte)((double)(240 - hue) / 60 * (max - min) + min), (byte)max, _A);
		else if (hue < 300)return Color((byte)((double)(hue - 240) / 60 * (max - min) + min), (byte)min, (byte)max, _A);
		else if (hue < 360)return Color((byte)max, (byte)min, (byte)((double)(360 - hue) / 60 * (max - min) + min), _A);
		else return Color(0, 0, 0, 0);
	}

	/// <summary>
	/// hsl値から色を生成
	/// </summary>
	/// <param name="hue">色相</param>
	/// <param name="sat">彩度</param>
	/// <param name="lum">輝度</param>
	/// <param name="_A">アルファ値</param>
	/// <returns>Color型に変換した結果</returns>
	static Color hsl(int hue, double sat, double lum, byte _A = 255)
	{
		double max, min;
		if (lum >= 0.5)
		{
			max = 255.0 * (lum + (1.0 - lum) * sat);
			min = 255.0 * (lum - (1.0 - lum) * sat);
		}
		else
		{
			max = 255.0 * (lum + lum * sat);
			min = 255.0 * (lum - lum * sat);
		}
		if (0 <= hue && hue < 60)return Color((byte)max, (byte)((double)hue / 60 * (max - min) + min), (byte)min, _A);
		else if (hue < 120)return Color((byte)((double)(120 - hue) / 60 * (max - min) + min), (byte)max, (byte)min, _A);
		else if (hue < 180)return Color((byte)min, (byte)max, (byte)((double)(hue - 120) / 60 * (max - min) + min), _A);
		else if (hue < 240)return Color((byte)min, (byte)((double)(240 - hue) / 60 * (max - min) + min), (byte)max, _A);
		else if (hue < 300)return Color((byte)((double)(hue - 240) / 60 * (max - min) + min), (byte)min, (byte)max, _A);
		else if (hue < 360)return Color((byte)max, (byte)min, (byte)((double)(360 - hue) / 60 * (max - min) + min), _A);
		else return Color(0, 0, 0, 0);
	}

	/// <summary>
	/// 色コードから色を生成
	/// </summary>
	/// <param name="_code">色コード(アルファ値を含まない)</param>
	/// <returns>Color型に変換した結果</returns>
	static Color code(unsigned int _code)
	{
		return Color((_code >> 6) & 0xff, (_code >> 4) & 0xff, (_code >> 2) & 0xff, _code & 0xff);
	}

	/// <summary>
	/// Color型の色をDxLibの関数で使える形式に変換
	/// </summary>
	/// <returns>変換結果</returns>
	unsigned int convert()
	{
		return GetColor(R, G, B);
	}

	/// <summary>
	/// 色相を計算
	/// </summary>
	/// <returns>色相</returns>
	int hue()
	{
		int max, min, a, b, plus;
		if (R > G)
		{
			if (G > B)
			{
				max = R; min = B;
				a = G; b = B;
				plus = 0;
			}
			else if (B > R)
			{
				max = B; min = G;
				a = R; b = G;
				plus = 240;
			}
			else
			{
				max = R; min = G;
				a = G; b = B;
				plus = 0;
			}
		}
		else
		{
			if (R > B)
			{
				max = G; min = B;
				a = B; b = R;
				plus = 120;
			}
			else if (G > B)
			{
				max = G; min = R;
				a = B; b = R;
				plus = 120;
			}
			else
			{
				max = B; min = R;
				a = R; b = G;
				plus = 240;
			}
		}
		double result = 60.0 * (a - b) / (max - min) + plus;
		if (result < 0)result += 360.0;
		return (int)result;
	}

	/// <summary>
	/// 彩度を計算
	/// </summary>
	/// <returns>彩度</returns>
	double sat()
	{
		if (R > G)
		{
			if (G > B)return (double)(R - B) / R;
			else if (B > R)return (double)(B - G) / B;
			else return (double)(R - G) / G;
		}
		else
		{
			if (R > B)return (double)(G - B) / G;
			else if (G > B)return (double)(G - R) / G;
			else return (double)(B - R) / B;
		}
	}

	/// <summary>
	/// 明度を計算
	/// </summary>
	/// <returns>明度</returns>
	double val()
	{
		if (R > G)return (std::max)(R, B);
		else return (std::max)(G, B);
	}
};

template<typename Ty>
concept field = std::semiregular<Ty> &&
	requires(Ty& elem1, Ty& elem2)
{
	{elem1 + elem2}->std::convertible_to<Ty>;
	{elem1 - elem2}->std::convertible_to<Ty>;
	{elem1 * elem2}->std::convertible_to<Ty>;
	{elem1 / elem2}->std::convertible_to<Ty>;
};

template<field PosTy>
requires std::convertible_to<PosTy, double> &&
	std::convertible_to<double, PosTy>
class Vector2
{
public:
	PosTy x = 0;
	PosTy y = 0;

	Vector2(){}
	Vector2(const PosTy _x, const PosTy _y): x(_x), y(_y)
	{}
	
	
	Vector2(std::initializer_list<PosTy> Ilist)
	{
		if (Ilist.size() >= 2)
		{
			x = *(Ilist.begin());
			y = *(Ilist.begin() + 1);
		}
		else
		{
			x = PosTy();
			y = PosTy();
		}
	}

	template<field Other>
	requires std::convertible_to<Other, PosTy>
	Vector2(const Vector2<Other>& _Right) :Vector2(static_cast<PosTy>(_Right.x), static_cast<PosTy>(_Right.y))
	{}

	static Vector2 circ(PosTy r, double angle)
	{
		return Vector2(static_cast<PosTy>(static_cast<double>(r) * (std::cos)(angle) + 0.5), static_cast<PosTy>(static_cast<double>(r) * (std::sin)(angle) + 0.5));
	}

	Vector2(const Vector2&) = default;
	Vector2(Vector2&&) = default;
	~Vector2() = default;
	Vector2& operator=(const Vector2&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator+(const Vector2& _Right)const&
	{
		return Vector2(x + _Right.x, y + _Right.y);
	}

	Vector2& operator+=(const Vector2& _Right)
	{
		x += _Right.x;
		y += _Right.y;
		return *this;
	}

	Vector2 operator-(const Vector2& _Right)const&
	{
		return Vector2(x - _Right.x, y - _Right.y);
	}

	Vector2& operator-=(const Vector2& _Right)
	{
		x -= _Right.x;
		y -= _Right.y;
		return *this;
	}

	PosTy operator*(const Vector2& _Right)const&
	{
		return x * _Right.x + y * _Right.y;
	}
};

template<field PosTy>
PosTy inner_prod(const Vector2<PosTy>& a, const Vector2<PosTy>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<field PosTy>
PosTy outer_prod(const Vector2<PosTy>& a, const Vector2<PosTy>& b)
{
	return a.x * b.y - a.y * b.x;
}