#pragma once

namespace tg
{
	//�������� ��� �������
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