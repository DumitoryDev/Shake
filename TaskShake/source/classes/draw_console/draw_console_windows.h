#pragma once

#include "../exceptions/exception.h"
#include "../../interfaces/i_draw/i_draw.h"

namespace tg
{
	
	class draw_console_windows:public i_draw
	{
		
	public:
		using i_draw::i_draw;
		draw_console_windows(void);
		

		void draw_info(const std::string& data) override;

		void draw_map(const map_matrix& data) override;

		void draw_snake(const snake& data) override;

		void draw_fruit(const fruit& data) override;

		void draw_score(std::size_t data) override;

		void draw(std::size_t x,std::size_t y, char chr) override;

		void clear() override
		{
			this->sz_height_ = 1; //так как рисуем с помощью курсора, то ставим его в начало
			system("cls");
		}

	private:
		HANDLE h_std_out_{};

		enum class console_color
		{
			black = 0,
			blue = 1,
			green = 2,
			cyan = 3,
			red = 4,
			magenta = 5,
			brown = 6,
			light_gray = 7,
			dark_gray = 8,
			light_blue = 9,
			light_green = 10,
			light_cyan = 11,
			light_red = 12,
			light_magenta = 13,
			yellow = 14,
			white = 15
		};

		void goto_xy(std::size_t X, std::size_t Y) const
		{
			const COORD coord = { static_cast<short>(X), static_cast<short>(Y) };
			if (!::SetConsoleCursorPosition(h_std_out_, coord))
			{
				throw game_error::m_win_api_exception(L"Error SetConsoleCursorPosition!", GetLastError());
			}
		} // перемещение курсора по координатам 

		void set_color(console_color color) const
		{
			if (!::SetConsoleTextAttribute(h_std_out_, 
				static_cast<WORD>(static_cast<int>(console_color::black) << 4 | static_cast<int>(color))))
			{
				throw game_error::m_win_api_exception(L"Error SetConsoleTextAttribute!", GetLastError());
			}
		}

		void hide_cursor(void) const;

		std::size_t sz_height_{};

		
	};

	
}
