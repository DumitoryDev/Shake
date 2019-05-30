#include"MapMatrix.h"

namespace task_game
{
	void map_matrix::fill_map()
	{
		if (!(this->height_ || this->wight_))
		{
			return;
		}

		for (std::size_t i = 0; i < this->wight_; ++i)
		{
			this->map_matrix_.emplace_back(height_);

			if (i == 0 || (i + 1) == this->wight_)
			{
				std::fill(this->map_matrix_[i].begin(), this->map_matrix_[i].end(), this->symbol_wall_);
				continue;
			}

			for (std::size_t j = 0; j < this->height_; ++j)
			{
				if (j != 0 && j + 1 != this->height_)
				{
					this->map_matrix_[i][j] = this->symbol_square_;
				}
				else
				{
					this->map_matrix_[i][j] = this->symbol_wall_;
				}

				
			}
		}
	}
}
