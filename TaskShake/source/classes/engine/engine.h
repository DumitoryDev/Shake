
#pragma once

#include "../../interfaces/i_draw/i_draw.h"
#include "../../abstract_classes/input/input.h"
#include "../game_object/point/point.h"
#include "../game_object/map_matrix/map_matrix.h"
#include "../game_object/snake/snake.h"
#include "../../interfaces/i_saver/i_saver.h"


namespace tg
{
	using shr_draw = std::shared_ptr<i_draw>;
	using shr_input = std::shared_ptr<input>;
	using shr_saver = std::shared_ptr<i_saver>;
		

	namespace config
	{
		enum class difficulty
		{
			low = 400,
			medium = 300,
			hard = 200
		};

		struct configurator //движок принимает конфигуратор для работы, в котором есть основный интрументы
		{
						
			shr_draw shr_draw{};
			shr_input shr_input{};
			shr_saver shr_saver{};

			std::string str_info_game = "\n\n\nPress CTRL + C to quick exit\nThis is snake game!\nYou need to eat as much fruit!"; //показывается во время игры
			std::string str_win_game = "****************************************** YOU WIN ******************************************"; //показывается после победы
		
		};
	}
	
	//главный класс игры, если можно так выразиться
	class engine
	{

	public:

		static engine & get_instance(void)
		{
			static engine engine;
			return engine;
		}

		void set_configuration(const config::configurator &data);

		void calculation(void);

		void quick_start_game(void); //автоматический запуск игры

		auto get_draw(void) const 
		{
			if (!this->configurator_.shr_draw)
					throw game_error::m_exception("Draw pointer is empty!");
			
			return this->configurator_.shr_draw;
		}

		auto get_input(void) const 
		{
			if (!this->configurator_.shr_input)
					throw game_error::m_exception("Input pointer is empty!");

			return this->configurator_.shr_input;
		}

		auto get_wight_map(void) const noexcept
		{
			return this->sz_wight_;
		}

		auto get_height_map(void) const noexcept
		{
			return this->sz_height_;
		}

		void save(void);

		auto  get_score(void) const noexcept
		{
			return this->sz_score_;
		}

		auto & get_setting(void) noexcept
		{
			return this->setting_game_;
		} //настройки игры, потом они сохраняются

		auto get_difficulty(void) const
		{
			return this->sz_difficulty_now_;
		}

		void default_param(void); // при перезапуске игры можно выставить параметры по умолчанию


		void set_count_score(const std::size_t sc)noexcept
		{
			if (sc)
				this->count_score_ = sc;
						
		}

		void create_snake(void) const;

		engine(const engine& other) = delete;
		engine(engine&& other) = delete;
		engine& operator=(const engine& other) = delete;
		engine& operator=(engine&& other) = delete;

	private:
		engine(void) = default;
		~engine(void);

		config::configurator configurator_{};

		std::size_t sz_score_{};
		std::size_t sz_wight_{};
		std::size_t sz_height_{};
		std::size_t count_score_{100};
		std::size_t sz_difficulty_now_{};


		std::thread input_thread_;
		std::atomic_bool is_alive_{false};
		std::atomic_bool is_alive_thread_{ false };
		std::atomic<input::direction> a_dir_{ input::direction::none };
		
		save::deserialize setting_game_{};
		
		void load_save(void);
		
		void first_draw(const snake& snake, map_matrix& map);
		void chk_snake_dir(const snake& data);
		void show_win(void) const;
		void check_config(void) const
		{
			if (!this->configurator_.shr_draw || !this->configurator_.shr_input || !this->configurator_.shr_saver)
			{
				throw game_error::m_exception("Empty configuration parameters!");
			}
		}

		void start_input_process(void);
		void start_draw_process(void);

		void draw_process(void);
		void draw_fruit(void);
		void input_process(void);
	};
}
