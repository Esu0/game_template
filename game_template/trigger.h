#pragma once
#include"gLibrary.h"

namespace objects
{
	namespace triggers
	{
		class Ellipse
		{
		private:
			double _a = 0, _b = 0;
		public:
			Ellipse(){}
			Ellipse(double a, double b) :_a(std::abs(a)), _b(std::abs(b))
			{}
			
			
		};

		class Rect
		{
		private:
			double _x = 0, _y = 0;
		public:
			Rect(){}
			Rect(double x, double y) :_x(x), _y(y)
			{}
		};
	}
}