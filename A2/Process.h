#pragma once

#include <iostream>
#include <thread>
#include "State.h"
#include "Suspended.h"
#include "Running.h"
#include "Ready.h"
#include "Terminated.h"
#include "Inactive.h"

using namespace std;

class Process
{
private:
	int readyTime;
	int serviceTime;
	int remainingTime;
	int runTime;
	State* state;
	int ID;
	char user;
	//thread processThread;

public:
	Process();
	~Process();
	Process(int, int, int, char);
	int getReadyTime();
	void setReadyTime(int);
	int getServiceTime();
	void setServiceTime(int);
	int getRemainingTime();
	void setRemainingTime(int);
	int getRunTime();
	void setRunTime(int);
	int getState();
	int getID();
	char getUser();
	void Suspend();
	void Wake(int, const char*);
	void Activate();
	void Terminate();
	bool IsActive();
	Process& operator=(Process&);
	void Run(int, const char*);
	thread RunThread(int, const char*);
	//void Initiate(int, const char*);
};
