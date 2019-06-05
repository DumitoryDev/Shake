#pragma once

#include "../point/point.h"



namespace tg
{
	class fruit
	{
	public:
		
		static auto & get_instance(void) noexcept
		{
			static fruit fruit;
			return fruit;
		}

		char get_symbol(void) const noexcept
		{
			return this->chr_symbol_;
		}

		const auto & get_point(void)const noexcept
		{
			return this->point_;
		}

		void set_point(const tg::point & point) noexcept
		{
			this->point_ = point;
		}

		void set_symbol(const char symbol) noexcept
		{
			this->chr_symbol_ = symbol;
		}
		
		void rand_fruit(long x_end, long y_end, long x_start = 0, long y_start = 0); //рандом точки по заданному диапазону

		fruit(const fruit &) = delete;
		fruit(fruit&&) = delete;
		fruit& operator = (const fruit &) = delete;
		fruit& operator = (fruit&&) = delete;
	private:
		fruit(void) = default;
		~fruit(void) = default;
		
		char chr_symbol_ = '*';
		point point_{};
		

	};
}
