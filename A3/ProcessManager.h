#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "Clock.h"
#include "Process.h"
#include <sstream>
#include "IOManager.h"

using namespace std;

class ProcessManager
{
private:
	ProcessManager();
	static ProcessManager* instance;
	void * handle;
	vector<Process> processes;
	int numberOfProcesses;
	int terminatedProcesses;
	vector<thread> processThreads;
public:
	~ProcessManager();
	static ProcessManager* getInstance();
	thread startThread();
	void run();
	void incrementTerminatedProcesses();
};

