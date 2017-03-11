#include "PCB.hpp"

namespace jgs
{
	namespace PCB
	{
		namespace
		{
			pcbState currentState = pcbState::NEW;
		}

		void set_state(pcbState newState)
		{
			currentState = newState;
		}

		pcbState get_state()
		{
			return currentState;
		}
	}
}