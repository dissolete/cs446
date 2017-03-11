

#ifndef __TIME_HPP_INCLUDED
#define __TIME_HPP_INCLUDED

#include <chrono>

namespace Time
{

	class Timer
	{
		public:

			Timer();

			void start();

			float restart();

			float elapsed();

		private:

			std::chrono::time_point<std::chrono::system_clock> m_initialTime;
	};

}


#endif

