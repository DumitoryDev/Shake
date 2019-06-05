#pragma once

#include "../../classes/player/player.h"
#include "../../classes/game_object/point/point.h"
#include "../../abstract_classes/input/input.h"



namespace tg
{
	// интерфейс для сохранения разными способами
	namespace save
	{
		//стуктура с информацией из файла настроек, если его не будет, то файл заполняется стандратными данными
		struct deserialize
		{

			std::map<input::direction, int> keys ={
			{ input::direction::up, 'w'},
			{ input::direction::down, 's'},
			{ input::direction::left, 'a'},
			{ input::direction::right, 'd'},
			{ input::direction::menu, 'm'},
			};
			std::multiset<player,std::greater<player>> set_players{player{50000, "KiNg_ShAkE"}}; //бог змейки
			std::size_t sz_difficulty{400};
			point p_map_size{40,60};

		};
	}
	

	class i_saver
	{
		
	public:
		i_saver(const i_saver& other) = delete;
		i_saver(i_saver&& other) = delete;
		i_saver& operator=(const i_saver& other) = delete;
		i_saver& operator=(i_saver&& other) = delete;
		virtual ~i_saver() = default;
		i_saver() = default;

		virtual save::deserialize get_info(void) = 0;
		virtual void set_info(const save::deserialize & data) = 0;
			

	};

}
