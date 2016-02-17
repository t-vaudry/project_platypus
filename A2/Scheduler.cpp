#include "Scheduler.h"


Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
}

User* Scheduler::GetUsers()
{
	return users;
}

void Scheduler::SetUsers(User* newUsers)
{
	users = newUsers;
}

int Scheduler::GetTimeQuantum()
{
	return timeQuantum;
}

void Scheduler::SetTimeQuantum(int t)
{
	timeQuantum = t;
}

void Scheduler::Run()
{

}