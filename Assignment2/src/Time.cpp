
#include "Time.hpp"


// Namespace instead of class just for fun :)

namespace Time
{

	typedef std::chrono::high_resolution_clock clock;
	
	namespace
	{
		clock::time_point programStart = clock::now();
	}

	void wait(unsigned int millisecondsToWait)
	{
		// Get current time
		clock::time_point localClock = clock::now();
		
		// Wait for the desired time
		while(std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - localClock).count() <= millisecondsToWait);
	}
	
	double elapsed()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(clock::now() - programStart).count();
	}
	
	void reset()
	{
		programStart = clock::now();
	}
}

