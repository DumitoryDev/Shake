#pragma once

namespace tg
{
	//стуктура для игроков
	struct player
	{
		std::size_t score{};
		std::string name{};
		

		bool operator < (const player & right) const
		{
			return   this->score < right.score;
		}


	    bool operator > ( const player & right) const 
		{
			return   this->score > right.score;
		}

	};


}