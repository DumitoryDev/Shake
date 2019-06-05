#pragma once
#include "../../classes/engine/engine.h"
#include "../../interfaces/i_saver/i_saver.h"

namespace tg
{
	// абстрактный класс для последующей реализации меню для игры
	class menu
	{
	public:
		virtual ~menu() = default;
		menu(void) = default;
		menu(const menu& other) = delete;
		menu(menu&& other) noexcept = delete;
		menu& operator=(const menu& other) = delete;
		menu& operator=(menu&& other) noexcept = delete;

		enum class operation
		{
			run = 0,
			score,
			edit_keys,
			edit_map,
			edit_difficulty,
			save,
			instruction,
			exit
		}; 

	virtual void show(void) = 0;
		
	protected:
		engine * engine_ = &engine::get_instance(); //получаем ссылку на engine, чтобы потом не вызывать постоянно
		save::deserialize * settings_{}; //указатель на структуру настроек, чтобы её сразу изменять, без вызова из engine 



	};

}
