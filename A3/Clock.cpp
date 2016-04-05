#include "Clock.h"

Clock::Clock()
{
	time = 0;
	handle = NULL;
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
	thread t = thread([=] { run(); });
	handle = t.native_handle();
	return t;
}

void Clock::run()
{
	while (true)
	{
		++time;
		Sleep(1);
	}
	TerminateThread(handle, 0);
}
