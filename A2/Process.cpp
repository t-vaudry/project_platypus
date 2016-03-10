#include <iostream>
#include "Process.h"

using namespace std;

Process::Process()
{
	readyTime = 0;
	serviceTime = 0;
	remainingTime = 0;
	runTime = 0;
	ID = 0;
	user = NULL;
	state = new Inactive();
}

Process::Process(int ready, int service, int id, char usr)
{
	readyTime = ready;
	serviceTime = service;
	remainingTime = service;
	ID = id;
	user = usr;
	state = new Inactive();
}

Process::~Process()
{
	//processThread.join();
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

int Process::getRunTime()
{
	return runTime;
}

void Process::setRunTime(int time)
{
	runTime = time;
}

int Process::getState()
{
	if (dynamic_cast<Ready*>(state))
		return 0;
	else if (dynamic_cast<Terminated*>(state))
		return 1;
	else if (dynamic_cast<Running*>(state))
		return 2;
	else if (dynamic_cast<Suspended*>(state))
		return 3;
	else
		return 4;//inactive

}

int Process::getID()
{
	return ID;
}

char Process::getUser()
{
	return user;
}

void Process::Suspend()
{
	state = new Suspended();
}

void Process::Wake(int time, const char* path)
{
	if (dynamic_cast<Ready*>(state))
	{
		IOManager IO;
		string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(ID) + ", Started \n";
		IO.Write(line, path);
	}

	state = new Running();
}

void Process::Activate()
{
	try 
	{
		if (!dynamic_cast<Inactive*>(state))
			throw "ERROR";
	}
	catch (char* s)
	{
		cout << s;
	}

	state = new Ready();
}

void Process::Terminate()
{
	state = new Terminated();
}

bool Process::IsActive()
{
	if (getState() != 1 && getState() != 4)
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

void Process::Run(int currentTime, const char* path)
{
	while (true)
	{
		state->execute(currentTime, user, ID, path);
		currentTime++;
	}
}

thread Process::RunThread(int currentTime, const char* path)
{
	return thread([=] { Run(currentTime, path); });
}

//void Process::Initiate(int currentTime, const char* path)
//{
//	thread processThread (&Process::Run, currentTime, path, Process());
//	//processThread(&Process::Run, currentTime, path, Process());
//	//processThread.join();
//}