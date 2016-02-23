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
	State* state;
	int ID;

public:
	Process();
	~Process();
	Process(int, int, int);
	int getReadyTime();
	void setReadyTime(int);
	int getServiceTime();
	void setServiceTime(int);
	int getRemainingTime();
	void setRemainingTime(int);
	int getState();
	int getID();
	void Suspend();
	void Wake(int, char, int, char*);
	void Activate();
	void Terminate();
	bool IsActive();
	Process& operator=(Process&);
	void Run(int, char, int, char*);
	void Initiate(int, char, int, const char*);
};
