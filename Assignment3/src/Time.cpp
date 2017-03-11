
#include "Time.hpp"


// Namespace instead of class just for fun :)

namespace Time
{

	Timer::Timer()
	{
		m_initialTime = std::chrono::system_clock::now();
	}

	void Timer::start()
	{
		m_initialTime = std::chrono::system_clock::now();
	}

	float Timer::restart()
	{
		std::chrono::duration<float> dt = std::chrono::seconds(0);
		std::chrono::time_point<std::chrono::system_clock> endTime = std::chrono::system_clock::now();

		dt = endTime - m_initialTime;
		m_initialTime = endTime;

		return dt.count();
	}

	float Timer::elapsed()
	{
		std::chrono::duration<float> dt = std::chrono::system_clock::now() - m_initialTime;
		return dt.count();
	}
}

