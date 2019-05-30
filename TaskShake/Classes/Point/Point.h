#pragma once
#include "../../GlobalHeaders/GlobalHeaders.h"

namespace task_game
{
		struct point
		{
			long  x{};
			long  y{};
		
			point(point const &) = default;
			point(point &&) = default;
			point & operator = (point const &) = default;
			point & operator = (point &&) = default;
			point() = default;
			~point() = default;
									

			point(const long x, const long y):x(x), y(y)
			{
				
			}
						
		    friend  bool operator == (const point & left, const point  & right ) noexcept
		    {
				return left.x == right.x && left.y == right.y;
		    }

			friend bool operator != (const point  & left, const point  & right)  noexcept
		    {
			 	return !(left == right);
		    }

			void rand(long x_end, long y_end, long x_start = 0, long y_start = 0);
		};

}
