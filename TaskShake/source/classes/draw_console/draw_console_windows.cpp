
#include "draw_console_windows.h"

namespace  tg
{
	draw_console_windows::draw_console_windows()
	{
		this->h_std_out_ = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if (h_std_out_ == INVALID_HANDLE_VALUE)
		{
			throw game_error::m_win_api_exception(L"Error GetStdHandle!", ::GetLastError());
		}

		if (!::SetConsoleDisplayMode(this->h_std_out_, CONSOLE_FULLSCREEN_MODE, nullptr))
		{
			throw game_error::m_win_api_exception(L"Error SetConsoleDisplayMode!", ::GetLastError());
		}
		
		this->hide_cursor();
	}

	void draw_console_windows::draw_info(const std::string& data)
	{
		if (!this->sz_height_) 
		{
			throw game_error::m_exception("Unknown or incorrect field height!");
		}
		set_color(console_color::yellow);
		goto_xy(0, this->sz_height_);
		std::cout << data << std::endl;
	}

	void draw_console_windows::draw_map(const map_matrix& data)
	{
		const auto w = data.get_width();
		const auto h = data.get_height();

		for (std::size_t i = 0; i < h; ++i)
		{
			for (std::size_t j = 0; j < w; ++j)
			{
				std::cout << data[i][j];
			}

			std::cout << std::endl;
		}

		this->sz_height_ = h;
	}

	void draw_console_windows::draw_shake(const shake& data)
	{
		const auto size_body = data.get_count_body();
		const auto symbol = data.get_symbol(); //символ змеи

		goto_xy(data[shake::head].x, data[shake::head].y);
		set_color(console_color::light_magenta);
		std::cout << data.get_symbol(); //сначала рисуем голову змеи одним цветом, а тело другим..

		for (std::size_t i = 1; i < size_body; ++i)
		{
			set_color(console_color::cyan);
			goto_xy(data[i].x, data[i].y);
			std::cout << symbol;
		}
		

	}

	void draw_console_windows::draw_fruit(const fruit& data)
	{
		const auto point = data.get_point();
		const auto symbol = data.get_symbol();

		set_color(console_color::red);
		goto_xy(point.x, point.y);

		std::cout << symbol;
		
	}

	void draw_console_windows::draw_score(const std::size_t data)
	{

	    this->draw_info("Score: " + std::to_string(data));
				
	}

	void draw_console_windows::draw(const std::size_t x, const std::size_t y, const char chr)
	{
		this->goto_xy(x, y);
		std::cout << chr;
		
	}

	void draw_console_windows::hide_cursor() const
	{
		CONSOLE_CURSOR_INFO struct_cursor_info;
		if (!GetConsoleCursorInfo(this->h_std_out_, &struct_cursor_info))
		{
			throw game_error::m_win_api_exception(L"Error GetConsoleCursorInfo!", ::GetLastError());
		}

		struct_cursor_info.bVisible = false;

		if (!SetConsoleCursorInfo(this->h_std_out_, &struct_cursor_info))
		{
			throw game_error::m_win_api_exception(L"Error SetConsoleCursorInfo!", ::GetLastError());
		}
	}
}
