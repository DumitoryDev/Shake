#include"shake.h"

namespace tg
{
	
	void shake::move(void)
	{
		if (this->deq_body_.empty())
		{
			return;
		}
		this->deq_body_.push_front(this->deq_body_.front());
		this->deq_body_.pop_back();
	}

	
}
