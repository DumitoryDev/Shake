#include"Point.h"
namespace task_game
{
	void point::rand(const long x_end, const long y_end, const long x_start, const long y_start)
	{
		if (x_start > x_end || y_start > y_end)
		{
			//exception
			return;
		}

		std::random_device dev;
		std::mt19937 gen(dev());
		std::uniform_int_distribution<> uid(x_start, x_end);
		this->x = uid(gen);
		uid = std::uniform_int_distribution<>(y_start, y_end);
		this->y = uid(gen);
	}
}
