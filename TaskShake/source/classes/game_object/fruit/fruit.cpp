#include "fruit.h"
#include "../../exceptions/exception.h"

namespace tg
{
	void fruit::rand_fruit(const long x_end, const long y_end, const long x_start, const long y_start)
	{
		if (x_start > x_end || y_start > y_end)
		{
			throw game_error::m_exception("Wrong values from random generator!");
		}

		std::random_device dev;
		std::mt19937 gen(dev());
		std::uniform_int_distribution<> uid(x_start, x_end);
		this->point_.x = uid(gen);
		uid = std::uniform_int_distribution<>(y_start, y_end);
		this->point_.y = uid(gen);
	}
}
