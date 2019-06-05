#include "engine.h"



namespace tg
{
	

	void engine::set_configuration(const config::configurator& data)
	{

		this->configurator_ = data;
		this->load_save();
		

	}

	void engine::start_input_process(void)
	{
		this->check_config(); //проверка, всё ли впорядке с конфигуратором
		input_thread_ = std::thread([this]()
		{
			try
			{
				while (this->is_alive_thread_) //Если вдруг пользователь закончил одну игру, поток не должен завершаться 
				{

					std::this_thread::sleep_for(std::chrono::milliseconds(this->sz_difficulty_now_));

					if (this->is_alive_)
					{
						this->input_process();
					}
					
				}
			
			}
			catch (const std::exception & ex)
			{
				std::cerr << ex.what() << std::endl;
				this->is_alive_ = false; 
			}
				
				
		});
		
	}

	

	void engine::start_draw_process(void)
	{
		this->check_config();
		try
		{
			this->draw_process();
		}
		catch (...)
		{
			this->is_alive_ = false;
			throw; 
			
		}
			
	
	}

	void engine::calculation(void)
	{
		auto& ref_snake = snake::get_instance();

		/*проверка стороны,  в которую мы движемся( если допустим, мы ползем вверх,
		а потом нажимаем назад + у нас есть хвост, то нужно менять направление*/
		this->chk_snake_dir(ref_snake); 
		
		ref_snake.move(); //добавляем новую голову

		switch (this->a_dir_) //в зависимости от направления меняем координату головы
		{
		case input::direction::up:
			ref_snake[snake::head].y--;
			break;

		case input::direction::left:
			ref_snake[snake::head].x--;
			break;

		case input::direction::right:
			ref_snake[snake::head].x++;
			break;

		case input::direction::down:
			ref_snake[snake::head].y++;
			break;

		default:
			return;
		}

		if (ref_snake[snake::head].x == 0 ||
			ref_snake[snake::head].y == 0 ||
			ref_snake[snake::head].x == this->sz_wight_ - 1 ||
			ref_snake[snake::head].y == this->sz_height_ - 1)
		{
			this->is_alive_ = false;
			return;
		}  //проверка на стены

		if (ref_snake.check_point(ref_snake[snake::head]))
		{
			this->is_alive_ = false;
			return;
		} //проверка на хвост

		if (ref_snake[snake::head] == fruit::get_instance().get_point())
		{
			ref_snake.push_tail(ref_snake.get_body().back()); 
			this->draw_fruit(); //рисуем фрукт заново
			this->sz_score_ += count_score_;
			if (this->sz_difficulty_now_ > 30)
			{
				this->sz_difficulty_now_ -= 10;
			}
		} //если достигли фрукта, то прибавляем хвост и очки, а так же усложняем игру
	}

	void engine::quick_start_game()
	{
		this->is_alive_ = true;
		this->create_snake();

		if (!this->is_alive_thread_) 
		{
			this->is_alive_thread_ = true;
			this->start_input_process();
		
		}//если позователь опять захочет поиграть, то поток не нужно запускать снова

		this->configurator_.shr_draw->clear(); //очистка консоли
		this->start_draw_process();
		
		
	}

	void engine::save(void)
	{
		this->check_config();
		this->configurator_.shr_saver->set_info(this->setting_game_); 
		this->sz_height_ = this->setting_game_.p_map_size.y;
		this->sz_wight_ = this->setting_game_.p_map_size.x;
	
		this->configurator_.shr_input->get_keys() = this->setting_game_.keys;
	}//сохранение во время игры, чтобы можно было сразу поменять некоторые параметры

	void engine::default_param()
	{
		this->check_config();
		this->sz_score_ = 0;
		this->sz_difficulty_now_ = this->setting_game_.sz_difficulty;
		this->configurator_.shr_input->set_direction(input::direction::none);
		this->a_dir_ = input::direction::none;
	}

	void engine::create_snake() const
	{
		snake::get_instance().clear(); 
		snake::get_instance().push_tail(point(this->sz_wight_ / 2, this->sz_height_ / 2)); // типа посередине
		
	}//при создании змеи, прошлые её настройки стираются


	void engine::load_save(void) 
	{
		this->check_config();
		this->setting_game_ = this->configurator_.shr_saver->get_info();
		this->configurator_.shr_input->get_keys() = this->setting_game_.keys;
		this->sz_difficulty_now_ = this->setting_game_.sz_difficulty;
		this->sz_height_ = this->setting_game_.p_map_size.y;
		this->sz_wight_ = this->setting_game_.p_map_size.x;
		
	}

	void engine::draw_fruit(void)
	{
		auto& ref_fruit = fruit::get_instance();
		/*
		 * 10000 раз фрукт пытается нарисоваться на карте без попадания на координаты змеи, 
		 * если у него не получается, я решил, что игрой выиграл
		 */
		std::size_t iteration = 10000;
		while (iteration-->1)
		{
			ref_fruit.rand_fruit(this->sz_wight_ - 2, this->sz_height_ - 2, 2, 2);
			if (!snake::get_instance().check_point(ref_fruit.get_point()))
			{
				this->configurator_.shr_draw->draw_fruit(ref_fruit);
				return;
			}//проверка, есть ли в теле змеи такая точка
		}
		this->sz_score_ += 50000;
		this->show_win();
		this->is_alive_ = false;
	}

	void engine::show_win(void) const
	{
		std::ostringstream os;
		os << this->configurator_.str_win_game<< "\nSCORE - " << this->sz_score_ << std::endl << "Type ENTER to continue.....";

		this->configurator_.shr_draw->clear();
		this->configurator_.shr_draw->draw_info(os.str()); //Показ информации о выигрыше
			
	}

	void engine::draw_process(void)
	{
		
		auto& ref_snake = snake::get_instance();
		auto& map = map_matrix::get_instance();
		this->first_draw(ref_snake, map); //первый раз рисуем карту и змею, которая не двигается
		while (this->is_alive_)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(this->sz_difficulty_now_));

			if (this->a_dir_ == input::direction::none)
			{
				continue;
			}

			if (this->a_dir_ == input::direction::menu)
			{
				this->is_alive_ = false;
				break;
			}

			this->configurator_.shr_draw->draw(ref_snake.get_body().back().x, ref_snake.get_body().back().y, ' '); //удаляем конец хвоста змеи, т.к. она перемещается

			this->calculation(); //изменения и првоерки змеи

			this->configurator_.shr_draw->draw_snake(ref_snake);
			this->configurator_.shr_draw->draw_score(this->sz_score_);
		}

	}

	void engine::input_process(void)
	{
		while (this->is_alive_)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(this->sz_difficulty_now_));
			const auto ptr = this->configurator_.shr_input->get_input_state(); //получаем нажатую клавишу 

			if (ptr == input::direction::none)
				continue;

			this->a_dir_ = ptr;
		}
	}

	void engine::first_draw(const snake& snake, map_matrix& map)
	{
		map.fill(this->sz_wight_, this->sz_height_);
		this->configurator_.shr_draw->draw_map(map);
		this->configurator_.shr_draw->draw_snake(snake);
		this->configurator_.shr_draw->draw_info(this->configurator_.str_info_game);
		this->draw_fruit();
	}

	

	void engine::chk_snake_dir(const snake& data)
	{
		if (data.get_count_body() ^ 1) //если у змеи есть хвост, то проверяем направление, и, если что, меняем его
		{
			if ((this->a_dir_ == input::direction::up ||
					this->a_dir_ == input::direction::down)
				&&
				(this->configurator_.shr_input->get_old_direction() == input::direction::down ||
					this->configurator_.shr_input->get_old_direction() == input::direction::up))
			{
				this->a_dir_ = this->configurator_.shr_input->get_old_direction();

				return;
			}

			if ((this->a_dir_ == input::direction::right ||
					this->a_dir_ == input::direction::left)
				&&
				(this->configurator_.shr_input->get_old_direction() == input::direction::right ||
					this->configurator_.shr_input->get_old_direction() == input::direction::left))
			{
				this->a_dir_ = this->configurator_.shr_input->get_old_direction();
			}
		}
	}

	

	engine::~engine()
	{
		try
		{
			this->save();
			this->is_alive_thread_ = false; //завершаем доп. поток
			if (this->input_thread_.joinable())
			{
				this->input_thread_.join();
			}
		}
		catch (...)
		{
		}
	}
}
