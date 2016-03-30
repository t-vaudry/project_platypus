#pragma once
#include <iostream>
#include <thread>
#include "Windows.h"
#include "Clock.h"

using namespace std;

class Process
{
private:
	int ID;
	int startTime;
	int endTime;

public:
	Process();
	~Process();
	void setID(int);
	int getID();
	void setStartTime(int);
	int getStartTime();
	void setEndTime(int);
	int getEndTime();
	thread startThread();
	void terminateThread(void* handle);
	void run();
};

