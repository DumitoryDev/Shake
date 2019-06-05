#pragma once
#include "../../abstract_classes/menu/menu.h"


namespace tg
{
	class game
	{
		using shr_menu = std::shared_ptr<menu>;
	public:
		static game& get_instance(void)
		{
			static game game;
			return game;
		}

		void set_menu(const shr_menu & menu)
		{
			this->shr_menu_ = menu;
		}

		void run(void) const
		{
			if (!shr_menu_)
			{
				throw game_error::m_exception("Menu is empty!");
			}
			this->shr_menu_->show();
		}
	private:
		shr_menu shr_menu_;
	};
}
