#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include "Windows.h"
#include "Clock.h"
#include "IOManager.h"
#include "InstructionParser.h"
#include "MemoryManager.h"
#include <sstream>
#include <random>

using namespace std;

class Process
{
private:
	int ID;
	int startTime;
	int endTime;
	void* handle;
	mutex m;

public:
	Process();
	~Process();
	Process(int, int, int);
	void setID(int);
	int getID();
	void setStartTime(int);
	int getStartTime();
	void setEndTime(int);
	int getEndTime();
	thread startThread();
	thread startRunTime();
	void terminateThread();
	void run();
	void checkRunTime();
	bool isStarted;
	void initialize(int, int, int);
};

