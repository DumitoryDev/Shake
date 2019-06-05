#pragma once

#include "../../exceptions/exception.h"

namespace tg
{

	//класс карты игры
	using matrix = std::vector<std::vector<char>>;
	class map_matrix
	{
		
	public:
		const static std::size_t max_size = 200;
		const static std::size_t min_size = 15;

		static auto & get_instance(void)
		{
			static map_matrix map_matrix;
			return map_matrix;
		}
		
		void fill(const std::size_t wight, const std::size_t height)
		{
			this->sz_width_ = wight;
			this->sz_height_ = height;
			this->fill_map();
		}

		void set_symbol(const char wall, const char square) noexcept
		{
			this->chr_symbol_wall_ = wall;
			this->chr_symbol_square_ = square;
		}

		auto get_width(void) const noexcept
		{
			return this->sz_width_;
		}

		auto get_height(void) const noexcept
		{
			return this->sz_height_;
		}

		const auto & get_map(void) const noexcept
		{
 			return this->vec_matrix_;
		}

		const auto & operator[](const std::size_t index) const
		{
			return this->vec_matrix_.at(index);
		}

		auto & operator[](const std::size_t index)
		{
			return this->vec_matrix_.at(index);
		}

		map_matrix& operator=(const map_matrix &) = delete;
		map_matrix& operator=(map_matrix&&) = delete;
		map_matrix(map_matrix&&) = delete;
		map_matrix(const map_matrix &) = delete;

	private:
			
		map_matrix(void) = default;
		~map_matrix(void) = default;
		matrix vec_matrix_{};
		std::size_t sz_width_{};
		std::size_t sz_height_{};
		char chr_symbol_wall_ = '$';
		char chr_symbol_square_ = ' ';

		void fill_map();

	};
	
}
