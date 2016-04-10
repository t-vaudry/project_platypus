#pragma once
#include <iostream>
#include <thread>
#include "Windows.h"
#include "Clock.h"
#include "IOManager.h"
#include "InstructionParser.h"
#include "MemoryManager.h"
#include <sstream>

using namespace std;

class Process
{
private:
	int ID;
	int startTime;
	int endTime;
	void* handle;
public:
	Process();
	~Process();
	Process(int, int, int);
	void setID(int);
	int getID();
	void setStartTime(int);
	int getStartTime();
	int getEndTime();
	thread startThread();
	thread startRunTime();
	void terminateThread();
	void run();
	void checkRunTime();
	void initialize(int, int, int);
};

