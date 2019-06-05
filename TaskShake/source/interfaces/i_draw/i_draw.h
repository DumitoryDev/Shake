#pragma once

#include "..//../classes/game_object/shake/shake.h"
#include "..//../classes/game_object/map_matrix/map_matrix.h"
#include "..//../classes/game_object/fruit/fruit.h"


namespace tg
{
	// интерфейс для разной отрисовки графики
	class i_draw
	{


	public:
		i_draw(const i_draw&) = delete;
		i_draw(i_draw&&) = delete;
		i_draw& operator=(const i_draw &) = delete;
		i_draw& operator=(i_draw&&) = delete;


		virtual ~i_draw(void) = default;
		virtual void draw_map(const map_matrix & data) = 0;
		virtual void draw_shake(const shake & data) = 0;
		virtual void draw_fruit(const fruit & data) = 0;
		virtual void draw_score(std::size_t data) = 0;
		virtual void draw_info(const std::string & data) = 0;
		virtual void draw(std::size_t x, std::size_t y, char chr) = 0; 
		virtual void clear() = 0;
		
	protected:
		i_draw(void) = default;
	};


}