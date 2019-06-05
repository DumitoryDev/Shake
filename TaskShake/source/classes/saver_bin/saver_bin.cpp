#include "saver_bin.h"
#include "../exceptions/exception.h"


namespace tg
{
	std::string saver_bin::str_path_ = { "bin//data.bin"};

	save::deserialize saver_bin::get_info()
	{
		this->file_.close();
		this->check_file_read();

		if (std::filesystem::file_size(str_path_) ==0) //если размер 0, то значит там ничего нет, возвращаем пустой объект с настройками по умолчанию
		{
			
			return {};
		}
			
		save::deserialize deserialize{};
		deserialize.set_players.clear();

		std::string str;
		this->file_ >> deserialize.p_map_size.x;
		this->file_ >> deserialize.p_map_size.y;
		this->file_ >> deserialize.sz_difficulty;
							
		int chr;

		for (auto & key : deserialize.keys)
		{
			this->file_ >> chr;
			key.second = chr;
		}
	
		player tmp;

		while (this->file_ >> tmp.name, this->file_ >> tmp.score)
		{
				
			deserialize.set_players.emplace(tmp);
		}

	
		return deserialize;

	}

	void saver_bin::set_info(const save::deserialize& data)
	{
		this->file_.close();
		this->check_file_write();
	
		std::ostringstream os;
		os << data.p_map_size.x << " " << data.p_map_size.y <<" ";

		os << data.sz_difficulty <<" ";

		for (const auto & key: data.keys)
		{
			os << key.second << " ";
		}
		
		this->file_ << std::endl;
		
		for (const auto & player : data.set_players)
		{
			os << player.name << " " << player.score;
		}
				
		this->file_<< os.str();
		this->file_<< std::endl;
		
	
	}

	void saver_bin::check_file(void) const
	{


		if (!std::filesystem::exists(str_path_))
		{

			if (!std::filesystem::create_directories(str_path_.substr(0, str_path_.find('/'))))
			{
				game_error::m_exception("Error creating folder!");
			}

		}

	}

	void saver_bin::check_file_write(void)
	{
		this->check_file();

		this->file_.open(str_path_ , std::ios::binary | std::ios::out);
		if (!file_.is_open() || !this->file_)
		{
			game_error::m_exception("Error open/create file!");
		}
	
	
	}

	void saver_bin::check_file_read(void)
	{
		this->check_file();

		this->file_.open(str_path_, std::ios::binary | std::ios::in);
		
		if (!this->file_.is_open()) //если файла нет, то пытаемся его создать 
		{
			this->check_file_write();
			this->file_.close();
			this->file_.open(str_path_, std::ios::binary | std::ios::in);
		}
		
			   
	}
}
