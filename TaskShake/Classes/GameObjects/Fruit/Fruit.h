#pragma once
#include"..//..//Point//Point.h"

namespace task_game
{
	class fruit
	{
	public:

		char get_symbol() const noexcept
		{
			return this->symbol_;
		}

		const point & get_point(point point)const noexcept
		{
			return this->point_;
		}

		explicit fruit(const task_game::point point, const char symbol = '@') : symbol_(symbol),point_(point)
		{
			
		}
				
		void rand_point(const long x_end, const long y_end, const long x_start, const long y_start)
		{
			point_.rand(x_end, y_end, x_start, y_start);
		}

	private:
		char symbol_{};
		point point_{};
		

	};
}
