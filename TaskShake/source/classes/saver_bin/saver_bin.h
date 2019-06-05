#pragma once
#include "../../interfaces/i_saver/i_saver.h"

namespace tg
{
	
	/*Класс для сохранения и загрузки данных
	 *создается папка в директории с игрой, в которой в итоге рождается файлик настроек
	 *
	 *
	 *
	 */
	class saver_bin:public i_saver
	{
		
	public:
		using i_saver::i_saver;
		save::deserialize get_info(void) override;
		void set_info(const save::deserialize& data) override;
				
	private:
		static std::string str_path_;
		std::fstream file_;

		void check_file(void) const;
		void check_file_write(void);
		void check_file_read(void);
		
		
	};

}
