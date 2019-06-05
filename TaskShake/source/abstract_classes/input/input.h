#pragma once
#include"..//..//..//TaskShake//stdafx.h"
namespace tg
{
	
	// абстрактный класс для приема данных с устройства и их обработки 
	class input
	{
	
	public:

		enum class direction { none = 0, up, down, left, right, menu };
		
		input(const input& other) = delete;
		input(input&& other) = delete;
		input& operator=(const input& other) = delete;
		input& operator=(input&& other) = delete;

		input() = default;
		virtual ~input() = default;
		virtual direction get_input_state() = 0;

		auto get_direction() const noexcept
		{
			return  this->dir_;
		}
		
		auto get_old_direction() const noexcept
		{
			return  this->old_dir_;
		}
		
		auto & get_keys(void) noexcept
		{
			return this->map_keys_;
		}

		void set_direction(const direction dir) noexcept
		{
			this->dir_ = dir;
		}
		

	protected:
		direction dir_ = direction::none;
		direction old_dir_ = direction::none;
		std::map< input::direction,int> map_keys_{};
		
	};

}
