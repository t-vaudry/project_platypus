#include <iostream>
#include "Process.h"

using namespace std;

Process::Process()
{
	readyTime = 0;
	serviceTime = 0;
	remainingTime = 0;
	state = new Ready();
}

Process::Process(int ready, int service)
{
	readyTime = ready;
	serviceTime = service;
	remainingTime = service;
	state = new Ready();
}

Process::~Process()
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

void Process::setServiceTime(int time)
{
	serviceTime = time;
}

int Process::getRemainingTime()
{
	return remainingTime;
}

void Process::setRemainingTime(int time)
{
	remainingTime = time;
}

int Process::getState()
{
	if (dynamic_cast<Ready*>(state))
		return 0;
	else if (dynamic_cast<Terminated*>(state))
		return 1;
	else if (dynamic_cast<Running*>(state))
		return 2;
	else 
		return 3; //Suspended

}

void Process::Suspend()
{
	state = new Suspended();
}

void Process::Wake(int time, char user, int process, char* path)
{
	if (dynamic_cast<Ready*>(state))
	{
		IOManager IO;
		string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Started \n";
		IO.Write(line, path);
	}

	state = new Running();
}

void Process::Terminate()
{
	state = new Terminated();
}

bool Process::IsActive()
{
	if (getState() != 1)
		return true;
	else
		return false;
}

Process& Process::operator=(Process& p)
{
	readyTime = p.readyTime;
	serviceTime = p.serviceTime;
	remainingTime = p.remainingTime;
	state = p.state;

	return p;
}