#include <iostream>
#include "Process.h"

using namespace std;

Process::Process()
{
	readyTime = 0;
	serviceTime = 0;
	remainingTime = 0;
	state = new Ready;
}

Process:~Process()
{
}

int Process::getReadyTime()
{
	return readyTime;
}

void Process::setReadyTime(int time)
{
	readyTime = time;
}

int Process::getServiceTime()
{
	return serviceTime;
}

void Process::setRemainingTime(int time)
{
	serviceTime = time;
}

int Process::getRemainingTime()
{
	return remainingTime;
}

void Process::Suspend()
{
}

void Process::Wake()
{
}

void Process::setRemainingTime(int time)
{
	remainingTime = time;
}