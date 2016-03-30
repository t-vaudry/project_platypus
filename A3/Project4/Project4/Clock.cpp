#include "Clock.h"

Clock::Clock()
{
	time = 0;
}

Clock::~Clock()
{
}

Clock* Clock::instance;

Clock* Clock::getInstance()
{
	if (instance == NULL)
	{
		instance = new Clock();
	}
	return instance;
}

int Clock::getTime()
{
	return time;
}

thread Clock::startThread()
{
	return thread([=] { run(); });
}

void Clock::run()
{
	while (true)
	{
		++time;
		Sleep(1);
	}
}
