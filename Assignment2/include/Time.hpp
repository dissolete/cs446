

#ifndef __TIME_HPP_INCLUDED
#define __TIME_HPP_INCLUDED

#include <chrono>

namespace Time
{

	void wait(unsigned int milliseconds);
	double elapsed();
	void reset();

}


#endif

