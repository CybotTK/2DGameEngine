#include "System/Timer.h"

#include <SDL2/SDL.h>

Timer::Timer()
{
	Reset();
}

Timer::Timer(float start)
{
	Set(start);
}

Timer::~Timer()
{
}

float Timer::Get() const
{
	float currentTime = MsToSec((float)SDL_GetTicks());
	
	return currentTime - m_timer;
}

void Timer::Set(float value)
{
	Reset();
	m_timer -= value;
}

void Timer::Reset()
{
	//int milliseconds
	unsigned int currentTicks = SDL_GetTicks();

	m_timer = MsToSec((float)currentTicks);
}

float Timer::MsToSec(float value) const
{
	return value / 1000.f;
}
