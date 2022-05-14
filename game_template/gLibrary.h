#pragma once
#include<cmath>

class Color
{
	using byte = unsigned char;
	Color(byte _R, byte _G, byte _B, byte _A)
		:R(_R), G(_G), B(_B), A(_A)
	{}

public:
	byte R = 0, G = 0, B = 0, A = 255;

	Color(unsigned int _code)
		:R((_code >> 4) & 0xff), G((_code >> 2) & 0xff), B(_code & 0xff)
	{}

	static Color rgb(byte _R, byte _G, byte _B, byte _A = 255)
	{
		return Color(_R, _G, _B, _A);
	}

	//0 <= hue < 360, 0 <= sat <= 1, 0 <= val <= 1
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

	static Color code(unsigned int _code)
	{
		return Color((_code >> 6) & 0xff, (_code >> 4) & 0xff, (_code >> 2) & 0xff, _code & 0xff);
	}

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

	double val()
	{
		if (R > G)return (std::max)(R, B);
		else return (std::max)(G, B);
	}
};

