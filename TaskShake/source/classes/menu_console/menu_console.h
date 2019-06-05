#pragma once
#include "../../abstract_classes/menu/menu.h"

#undef max
namespace tg
{
	
	class menu_console: public menu
	{
		
	public:
		void show() override;
	private:
		const std::size_t sz_delay_ = 1000;
		void config_engine(void);
	    void new_game(void) const;
		void show_score(void) const;
		void main_menu(void);
		void edit_keys(void) const;
	    void edit_map(void) const;
		void edit_difficulty(void) const;
		void save_settings(void) const;
		void show_instruction(void) const;

		static void clear_cin()
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		const std::map<operation, std::function<void(menu_console&)>> map_func_ = {
		{operation::run,&menu_console::new_game},
		{operation::score,&menu_console::show_score},
		{operation::edit_keys,&menu_console::edit_keys},
		{operation::edit_map,&menu_console::edit_map},
		{operation::edit_difficulty, &menu_console::edit_difficulty},
		{operation::save,&menu_console::save_settings},
		
		{operation::instruction,&menu_console::show_instruction} };
	};

}
