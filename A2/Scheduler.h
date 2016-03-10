#pragma once
#include "User.h"
#include "IOManager.h"
#include <vector>
#include <thread>
class Scheduler
{
private:
	vector<User> users;
	IOManager IO;
	int timeQuantum;
	int currentTime;
	Process* activeProcesses;
	vector<thread> processThreads;
public:
	Scheduler();
	~Scheduler();
	vector<User> GetUsers();
	void SetUsers(vector<User>);
	int GetTimeQuantum();
	void SetTimeQuantum(int);
	void Run(const char*, const char*);
	thread RunThread(const char*, const char*);
};


