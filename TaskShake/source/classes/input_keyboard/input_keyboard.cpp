#include "input_keyboard.h"
namespace tg
{
	
	input::direction input_keyboard::get_input_state(void)
	{
		if (::_kbhit())
		{
			const char chr = ::_getch();
			
			const auto res_find = std::find_if(this->map_keys_.cbegin(),this->map_keys_.cend(),[chr](const auto & ptr )
			{
					return ptr.second == chr;
			});

			if (res_find == this->map_keys_.cend() || res_find->first == this->dir_)
				return direction::none;

			this->old_dir_ = this->dir_; //запоминаем старую клавишу чтобы, если что, поменять направление
			this->dir_ = res_find->first;


			return this->dir_;
		}
		return direction::none;
	}

	
}
