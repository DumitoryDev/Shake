#include "../source/classes/menu_console/menu_console.h"
#include "../source/classes/game/game.h"
#include "../source/classes/exceptions/exception.h"

int main() 
{
	try
	{
		const std::shared_ptr<tg::menu> ptr = std::make_shared<tg::menu_console>();
		auto& game = tg::game::get_instance();
		game.set_menu(ptr);
		game.run();
		
		return 0;
	}
	catch (const game_error::m_win_api_exception & err)
	{
		std::wcerr << err.GetMessage();
	}
	catch(const std::exception & err)
	{
		std::cerr << err.what();
	}
	catch(...)
	{
		std::cerr << "Error!";
	}
	return -1;
    
}
