#include <iostream>
#include "Process.h"

using namespace std;

Process::Process()
{
	readyTime = 0;
	serviceTime = 0;
}

Process:~Process()
{
}

int Process::GetReadyTime()
{
	return readyTime;
}

void Process::SetReadyTime(int time)
{
	readyTime = time;
}

int Process::GetServiceTime()
{
	return serviceTime;
}

void Process::SetServiceTime(int time)
{
	serviceTime = time;
}

void Process::Suspend()
{
}

void Process::Wake()
{
}