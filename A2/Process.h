#pragma once
#include <thread>
#include <Windows.h>
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
	int ReadyTime;
	int serviceTime;
	int remainingTime;
	int runTime;
	State* state;
	int ID;
	char user;
	void * threadHandler;

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
	void activate();
	void suspend(int&, const char*);
	void wake(int&, const char*);
	void terminate(int&, const char*);
	bool isActive();
	Process& operator=(Process&);
	void run(int*, const char*);
	thread runThread(int*, const char*);
};
