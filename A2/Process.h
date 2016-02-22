#pragma once

#include <iostream>
#include <thread>
#include "State.h"
#include "Suspended.h"
#include "Running.h"
#include "Ready.h"
#include "Terminated.h"

using namespace std;

class Process: public thread
{
private:
	int readyTime;
	int serviceTime;
	int remainingTime;
	State* state;
public:
	Process();
	~Process();
	Process(int, int);
	int getReadyTime();
	void setReadyTime(int);
	int getServiceTime();
	void setServiceTime(int);
	int getRemainingTime();
	void setRemainingTime(int);
	int getState();
	void Suspend();
	void Wake(int, char, int, char*);
	void Terminate();
	bool IsActive();
	Process& operator=(Process&);
};
