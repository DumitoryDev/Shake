#pragma once
#include "..//..//.//..//..//task_snake//stdafx.h"


namespace tg
{
		struct point
		{
			std::size_t  x{};
			std::size_t  y{};
		
			point(point const &) = default;
			point(point &&) = default;
			point & operator = (point const &) = default;
			point & operator = (point &&) = default;
			point() = default;
			~point() = default;
									

			point(const std::size_t x, const std::size_t y):x(x), y(y)
			{
				
			}
						
		    friend bool operator == (const point & left, const point  & right ) noexcept
		    {
				return left.x == right.x && left.y == right.y;
		    }

			friend bool operator != (const point  & left, const point  & right)  noexcept
		    {
			 	return !(left == right);
		    }
						
		};

}
