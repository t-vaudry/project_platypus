#pragma once
#include "User.h"
#include "IOManager.h"
#include <vector>
class Scheduler
{
private:
	vector<User> users;
	IOManager IO;
	int timeQuantum;
	int currentTime;

public:
	Scheduler();
	~Scheduler();
	vector<User> GetUsers();
	void SetUsers(vector<User>);
	int GetTimeQuantum();
	void SetTimeQuantum(int);
	void Run(const char*);
	thread RunThread(const char*);
};


