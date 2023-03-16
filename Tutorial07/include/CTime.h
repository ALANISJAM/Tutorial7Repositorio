#include <Windows.h>
#pragma once
class 
CTime
{
public:
CTime();
~CTime();

void 
init();

void 
update();

void 
render();

void 
destroy();

float m_deltaTime;
private:

	
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_timerFrequency;
};

