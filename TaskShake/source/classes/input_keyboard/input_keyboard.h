#pragma once

#include "../../abstract_classes/input/input.h"


namespace tg
{
	//реализаци€ прин€ти€ данных с консоли под виндовс 
	class input_keyboard : public input
	{

	public:
		using input::input;

		direction get_input_state(void) override;
				
	};


}
