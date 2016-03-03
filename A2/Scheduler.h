#pragma once
#include <vector>
#include <Windows.h>
#include "User.h"
#include "IOManager.h"

class Scheduler
{
private:
	vector<User> users;
	IOManager IO;
	int timeQuantum;
	int currentTime;
	vector<thread> processThreads;
public:
	Scheduler();
	~Scheduler();
	vector<User> getUsers();
	void setUsers(vector<User>);
	int getTimeQuantum();
	void setTimeQuantum(int);
	void run(const char*, const char*, const char*);
	thread runThread(const char*, const char*, const char*);
};


