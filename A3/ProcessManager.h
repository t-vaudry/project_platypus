#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include "Clock.h"
#include "Process.h"

using namespace std;

class ProcessManager
{
private:
	ProcessManager();
	static ProcessManager* instance;
	Process* processes;
	int numberOfProcesses;
	vector<thread> processThreads;
public:
	~ProcessManager();
	static ProcessManager* getInstance();
	thread startThread();
	void run();
};

