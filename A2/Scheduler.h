#pragma once
#include "User.h"
#include "IOManager.h"
class Scheduler
{
private:
	User* users;
	IOManager input_output_manager;
	int timeQuantum;


public:
	Scheduler();
	~Scheduler();
	User* GetUsers();
	void SetUsers(User*);
	int GetTimeQuantum();
	void SetTimeQuantum(int);
	void Run();
};

