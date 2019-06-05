#include "menu_console.h"
#include "../saver_bin/saver_bin.h"
#include "../draw_console/draw_console_windows.h"
#include "../input_keyboard/input_keyboard.h"


namespace tg
{
	void menu_console::show()
	{

		this->config_engine();
		this->main_menu();

	}

	void menu_console::config_engine() 
	{

		config::configurator configurator;
		configurator.shr_saver = std::make_shared<saver_bin>();
		configurator.shr_draw = std::make_shared<draw_console_windows>();
		configurator.shr_input = std::make_shared<input_keyboard>();

		this->engine_->set_configuration(configurator);
		this->settings_ = &this->engine_->get_setting();


	}

	void menu_console::new_game() const
	{
		
		this->engine_->quick_start_game();
		this->engine_->get_draw()->clear();
		const auto score = this->engine_->get_score();
		std::cout << "You score - " << score << std::endl;
		
		const auto res = std::prev(this->settings_->set_players.cend());
		auto is_worthy{false};
		if (this->settings_->set_players.size() >= 10 && res->score < score)
		{
					
			this->settings_->set_players.erase(res);
			is_worthy = true;
		}

		else if(this->settings_->set_players.size() < 10)
		{
			is_worthy = true;
		}

		if (is_worthy)
		{
			std::cout << "Type your name: " << std::endl;
			std::string name;
			while (true)
			{

				std::cin >> name;


				const auto res_name = std::find_if(
				this->settings_->set_players.cbegin(),
				this->settings_->set_players.cend(), 
				[name](const auto & el)
				{
					return  el.name == name;
				});

				if (res_name != this->settings_->set_players.cend() || name.empty())
				{
					std::cout << "This name is now exist or name is empty! Pleas, type new name..." << std::endl;
					continue;
				}
				break;
			}

			this->settings_->set_players.emplace(player{ score,name });

		}
		
		this->engine_->save();
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sz_delay_));
		this->engine_->get_draw()->clear();
		this->engine_->default_param();
		
	}

	void menu_console::show_score() const
	{

		std::cout << "***********************************SCORE***********************************" << std::endl;
	
		for (const auto & player : this->settings_->set_players)
		{
			std::cout << player.name << " - " << player.score << std::endl;
		}


	}

	void menu_console::main_menu()
	{
		
		while (true)
		{

			
			system("cls");
			
			std::cout << "1 - Start new game\n2 - Best players\n3 - Change keys\n4 - Resize playing map\n5 - Edit difficulty\n6 - Save settings\n7 - Show Instruction\n8 - Exit" << std::endl;
			std::size_t choice;
			std::cin >> choice;

			if (choice == 8)
			{
				break;
			}

			if (choice > this->map_func_.size() || choice <=0)
			{
				std::cout << "Incorrect choice..." << std::endl;
				std::cout << "Press enter two times..." << std::endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(this->sz_delay_));
				continue;
			}

			system("cls");
			this->map_func_.find(static_cast<operation>(choice-1))->second(*this);
			std::cout << std::endl;
			std::cout << "Press enter..." << std::endl;
			std::cin.get();
			clear_cin();
								
			
		}

	}
	

	void menu_console::edit_keys() const
	{

		std::cout << "Type the five keys (UP,DOWN,LEFT,RIGHT,MENU)\nIf you want to immediately apply the settings, then click save settings in the main menu." << std::endl;
		char val{};
		for (auto & key : this->engine_->get_setting().keys)
		{
			std::cin >> val;
		
			auto res_find = std::find_if(this->settings_->keys.cbegin(), this->settings_->keys.cend(), [val](const auto & data)
			{
					return data.second == val;
			});
			if (res_find != this->settings_->keys.cend())
			{
				continue;
			}
			key.second = val;
					
		}
	
		std::cout << "DONE!...";
					   
	}

	void menu_console::edit_map() const
	{

		std::cout << "Type wight and height map.. After that, restart the game" << std::endl;
		std::size_t h{};
		std::size_t w{};
		while (true)
		{
			std::cin >> w;
			std::cin >> h;
			if (w < map_matrix::min_size || w > map_matrix::max_size || h < map_matrix::min_size || h > map_matrix::max_size)
			{
				std::cout << "Incorrect parameters!... Min - " << map_matrix::min_size << " " << " max - " << map_matrix::max_size;
				continue;
			}

			break;
		}

		this->settings_->p_map_size.x = w;
		this->settings_->p_map_size.y = h;
		this->engine_->save();
		::exit(0);
		
	}

	void menu_console::edit_difficulty() const
	{

		std::cout << "Choose the difficulty of the game..\n1 - low\n2 - medium\n3 - hard\n";
		std::size_t choice{};
		std::cin >> choice;
		switch (choice)
		{
			
		case 1:
			this->settings_->sz_difficulty = static_cast<std::size_t>(config::difficulty::low);
			break;
		case 2:
			this->settings_->sz_difficulty = static_cast<std::size_t>(config::difficulty::medium);
			break;
		case 3:
			this->settings_->sz_difficulty = static_cast<std::size_t>(config::difficulty::hard);
			break;
		default:
			std::cout << "Incorrect choice!" << std::endl;
			
		}


	}

	void menu_console::save_settings() const
	{

		this->engine_->save();
	}

	void menu_console::show_instruction() const
	{


		std::cout << "This is shake game!\nYou need to eat as much fruit!\nKEYS:\nPress CTRL + C to quick exit\nUP,DOWN,LEFT,RIGHT,MENU - ";
		for (const auto & key : this->settings_->keys)
		{
			std::cout << static_cast<char>(key.second) << " ";
		}
		


	}
}
