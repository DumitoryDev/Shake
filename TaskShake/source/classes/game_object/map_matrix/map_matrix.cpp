
#include "map_matrix.h"

namespace tg
{
	void map_matrix::fill_map(void)
	{
		if ((this->sz_height_ < min_size || this->sz_width_ < min_size) || this->sz_height_ > max_size || this->sz_width_ > max_size)
		{
			throw game_error::m_exception("Invalid parameters in matrix!");
		}

		for (std::size_t i{}; i < this->sz_height_; ++i)
		{
			this->vec_matrix_.emplace_back(sz_width_);
			//если у нас певра€ или последн€€ строка, то сразу еЄ заполн€ем
			if (i == 0 || (i + 1 == this->sz_height_))
			{
				std::fill(this->vec_matrix_[i].begin(), this->vec_matrix_[i].end(), this->chr_symbol_wall_);
				continue;
			}
			

			for (std::size_t j{}; j < this->sz_width_; ++j)
			{
				if (j != 0 && j + 1 != this->sz_width_)
				{
					this->vec_matrix_[i][j] = this->chr_symbol_square_;
				}
				else
				{
					this->vec_matrix_[i][j] = this->chr_symbol_wall_;
				}
								
			}
		}
	}

	
}
