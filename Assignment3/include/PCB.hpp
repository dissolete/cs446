#ifndef __PCB_HEADER_INCLUDED
#define __PCB_HEADER_INCLUDED

namespace jgs
{

	namespace PCB
	{
		enum pcbState
		{
			NEW, READY, WAITING, RUNNING, TERMINATED
		};

		void set_state(pcbState newState);

		pcbState get_state();
	}
}

#endif
