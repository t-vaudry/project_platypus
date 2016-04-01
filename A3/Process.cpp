#include "Process.h"

using namespace std;

Process::Process()
{
	handle = NULL;
}

Process::Process(int id, int start, int end)
{
	ID = id;
	startTime = start;
	endTime = end;
	handle = NULL;
}

Process::~Process()
{
}

void Process::setID(int id)
{
	ID = id;
}

int Process::getID()
{
	return ID;
}

void Process::setStartTime(int t)
{
	startTime = t;
}

int Process::getStartTime()
{
	return startTime;
}

void Process::setEndTime(int t)
{
	endTime = t;
}

int Process::getEndTime()
{
	return endTime;
}

thread Process::startThread()
{
	thread t([&] { run(); });
	handle = t.native_handle();
	return t;
}

thread Process::startRunTime()
{
	return thread([=] { checkRunTime(); });
}

void Process::terminateThread()
{
	//to do if handle is NULL throw
	TerminateThread(handle, 0);
}

void Process::run()
{
	isStarted = true;
	m.lock();//try accessing m. If
	//to do
	m.unlock();
}

void Process::checkRunTime()
{
<<<<<<< HEAD
=======
	while (!isStarted);

>>>>>>> a06924597d352251e44d9eae1fee0c45eca7b8bd
	while (Clock::getInstance()->getTime() < endTime);
	terminateThread();
}