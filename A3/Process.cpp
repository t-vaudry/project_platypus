#include <iostream>
#include "Process.h"

using namespace std;


Process::Process()
{
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
	return std::thread([=] { run(); });
}

void Process::terminateThread(void* handle)
{
	terminateThread(handle);
}