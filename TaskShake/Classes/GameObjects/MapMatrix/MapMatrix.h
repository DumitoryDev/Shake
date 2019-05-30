#pragma once
#include "..//..//..//GlobalHeaders/GlobalHeaders.h"
#include "../../Point/Point.h"


namespace task_game
{
		
	using matrix = std::vector<std::vector<char>>;
	class map_matrix
	{
		void fill_map();


	public:
		map_matrix(const std::size_t wight,
			const std::size_t height, 
			const char symbol_wall = '$', 
			const char symbol_square = ' '):
		wight_(wight),
		height_(height),
		symbol_wall_(symbol_wall),
		symbol_square_(symbol_square)
		{
			this->fill_map();
		}




		const matrix & get_map() const noexcept
		{
 			return this->map_matrix_;
		}


	private:
		matrix map_matrix_{};
		std::size_t wight_{};
		std::size_t height_{};
		char symbol_wall_{};
		char symbol_square_{};

	};
	
}
