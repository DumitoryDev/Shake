#pragma once
#include"..//..//Point//Point.h"
#include "..//..//..//GlobalHeaders/GlobalHeaders.h"
namespace task_game
{
	class shake
	{

	public:
		const static size_t head = 0;

		explicit shake(const point point, const char symbol = 'o'):symbol_(symbol)
		{
  			this->body_.push_back(point);
		}

		char get_symbol() const noexcept
		{
			return this->symbol_;
		}

		const std::deque<point> & get_body() const noexcept
		{
			return this->body_;
		}

		size_t get_score() const noexcept
		{
			return this->score_;
		}

		void inc_score(const size_t inc) noexcept
		{
			this->score_ += inc;
		}

		void move()
		{
			this->body_.push_front(this->body_.front());
			this->body_.pop_back();
		}

	private:
		size_t score_{};
		char symbol_{ };
		std::deque<point> body_{};

	};

	


}