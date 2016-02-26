#include "Scheduler.h"
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include <Windows.h>

using namespace std;

Scheduler::Scheduler()
{
	currentTime = 1;
}

Scheduler::~Scheduler()
{
	for (int i = 0; i < processThreads.size(); i++)
		processThreads[i].join();
}

vector<User> Scheduler::GetUsers()
{
	return users;
}

void Scheduler::SetUsers(vector<User> newUsers)
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

void Scheduler::Run(const char* inputPath, const char* outputPath)
{
	string input;
	input = IO.Read(inputPath);

	stringstream inputStream(input);

	//Parse input file
	//Get time quantum
	string timeQ;
	getline(inputStream, timeQ);
	timeQuantum = stoi(timeQ);

	int numInt;

	//Get users
	while (true)
	{
		//Get user name
		string n;
		getline(inputStream, n, ' ');

		if (n == "")
			break;

		//Get number of processes
		string num;
		getline(inputStream, num);
		numInt = stoi(num);

		//Create all processes
		vector<Process*> processes;// = new Process[numInt];
		for (int i = 0; i < numInt; i++)
		{
			string start;
			getline(inputStream, start, ' ');

			string service;
			getline(inputStream, service);

			Process* p = new Process(stoi(start), stoi(service), i, n[0]);

			processes.push_back(p);
			//processes[i].join(); to do
		}

		//Create users
		User u(n, numInt, processes);
		users.push_back(u);
	}

	for (int i = 0; i < users.size(); i++)
	{
		vector<Process*> userProcesses;// = users[i].GetAllProcesses();
		userProcesses = users[i].GetAllProcesses();
		
		for (int j = 0; j < users[i].GetNumberOfProcesses(); j++)
		{
			//thread t = userProcesses[j].RunThread(currentTime, path);
			processThreads.push_back(userProcesses[j]->RunThread(currentTime, outputPath));
			//userProcesses[j].Initiate(currentTime, path);
		}
	}



	int numberOfFinishedUsers = 0;

	//Get number of active processes for each user
	while (true) //NEW CONDITION; should change
	{
		//foreach user. foreach process. if arrival time == current time, state = ready
		for (int i = 0; i < users.size(); i++)
		{
			vector<Process*> pList;// = users[i].GetAllProcesses();
			pList = users[i].GetAllProcesses();

			for (int j = 0; j < users[i].GetNumberOfProcesses(); j++)
			{
				if (pList[j]->getReadyTime() <= currentTime)
					pList[j]->Activate();
			}
		}
		//Get number of active users
		int activeUsers = 0;
		for (int i = 0; i < users.size(); i++)
			if (users[i].IsActive())
				activeUsers++;

		//if no users left, break
		if(activeUsers == 0)
			break;

		//Get time quantum per user
		int timePerUser = timeQuantum / activeUsers;
		vector<Process*> activeProcesses;

		for (int i = 0; i < users.size(); i++)
		{
			vector<Process*> p;// = users[i].GetActiveProcesses();
			p = users[i].GetActiveProcesses();

			if (users[i].ActiveProcesses() == 0)
				break;

			int timePerProcess = timePerUser / users[i].ActiveProcesses();

			for (int j = 0; j < p.size(); j++)
			{
				//set the runtime of each Process
				p[j]->setRunTime(timePerProcess);
				activeProcesses.push_back(p[j]);
			}

		}

		for(int i = 0; i < activeProcesses.size(); i++)
		{
			if( i != 0 )
			{
				activeProcesses[i-1]->Suspend();
				if(activeProcesses[i-1]->getRemainingTime() == 0)
				{
					activeProcesses[i-1]->Terminate();
				}
			}

			activeProcesses[i]->Wake(currentTime, outputPath);
			if(activeProcesses[i]->getRunTime() >= activeProcesses[i]->getRemainingTime())
			{
				Sleep(activeProcesses[i]->getRemainingTime() * 1000);
				activeProcesses[i]->setRemainingTime(0);
				currentTime += activeProcesses[i]->getRemainingTime();
			}
			else
			{
				Sleep(activeProcesses[i]->getRunTime() * 1000);
				activeProcesses[i]->setRemainingTime(activeProcesses[i]->getRemainingTime()-activeProcesses[i]->getRunTime());
				currentTime += activeProcesses[i]->getRunTime();
			}
		}
	}
}

thread Scheduler::RunThread(const char* inputPath, const char* outputPath)
{
	return std::thread([=] { Run(inputPath, outputPath); });
}