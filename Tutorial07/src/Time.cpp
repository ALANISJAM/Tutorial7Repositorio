#include "Time.h"



	Time::Time()
	{
		
	}

	Time::~Time()
	{
	}

	void Time::init()
	{
		QueryPerformanceCounter(&m_lastTime);
		QueryPerformanceFrequency(&m_timerFrequency);
	}
	

	void Time::update()
	{
		QueryPerformanceCounter(&m_currentTime);
		m_deltaTime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrequency.QuadPart;
		m_lastTime = m_currentTime;
		m_deltaTime = min(m_deltaTime, 0.1f);
	}

	void Time::render()
	{
	}

	void Time::destroy()
	{
	}



