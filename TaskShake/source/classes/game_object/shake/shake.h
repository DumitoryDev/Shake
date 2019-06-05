#pragma once
#include "../point/point.h"

namespace tg
{
	
	class shake
	{
	
	public:
 
	    static shake& get_instance(void)
	    {
			static shake shake;
			return shake;
	    }

		const static size_t head = 0;
		

		void set_point(const point& point)
		{
  			this->deq_body_.push_back(point);
		}

		char get_symbol(void) const noexcept
		{
			return this->chr_symbol_;
		}

		const auto & get_body(void) const noexcept
		{
			return this->deq_body_;
		}

		auto get_score(void) const noexcept
		{
			return this->sz_score_;
		}

		void inc_score(const size_t inc) noexcept
		{
			this->sz_score_ += inc;
		}

		void move(void);

		auto get_count_body(void) const noexcept
		{
			return this->deq_body_.size();
		}

		const auto & operator[](const std::size_t index) const
		{
			return this->deq_body_.at(index);
		}

		auto & operator[](const std::size_t index)
		{
			return this->deq_body_.at(index);
		}

		void push_tail(const point & data)
		{
			this->deq_body_.push_back(data);
		}

		auto check_point(const point & data) const 
		{
			return std::find(std::next(this->deq_body_.cbegin()), this->deq_body_.cend(), data) != deq_body_.cend();
		}

		void clear(void)
		{
			this->deq_body_.clear();
		}

		shake(const shake &) = delete;
		shake(shake &&) = delete;
		shake & operator = (const shake &) = delete;
		shake & operator = (shake &&) = delete;
		
	private:
		~shake(void) = default;
		
		shake(void) = default;
		
		size_t sz_score_{};
		const char chr_symbol_ = 'o';
		std::deque<point> deq_body_{};

	};

	


}
