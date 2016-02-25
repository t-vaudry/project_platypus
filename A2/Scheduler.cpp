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

void Scheduler::Run(const char* path)
{
	string input;
	input = IO.Read(path);

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
		Process* processes = new Process[numInt];
		for (int i = 0; i < numInt; i++)
		{
			string start;
			getline(inputStream, start, ' ');

			string service;
			getline(inputStream, service);

			Process p(stoi(start), stoi(service), i, n[0]);

			processes[i] = p;
			//processes[i].join(); to do
		}

		//Create users
		User u(n, numInt, processes);
		users.push_back(u);

		for (int i = 0; i < users.size(); i++)
		{
			Process* userProcesses = users[i].GetAllProcesses();
			for (int j = 0; j < users[i].GetNumberOfProcesses(); j++)
				userProcesses[j].Initiate(currentTime, path);
		}
	}

	int numberOfFinishedUsers = 0;

	//Get number of active processes for each user
	while (true) //NEW CONDITION; should change
	{
		//foreach user. foreach process. if arrival time == current time, state = ready
		for (int i = 0; i < users.size(); i++)
		{
			Process* pList = users[i].GetAllProcesses();
			for (int j = 0; j < users[i].GetNumberOfProcesses(); j++)
			{
				if (pList[j].getReadyTime() <= currentTime)
					pList[j].Activate();
			}
		}

		//Get number of active users
		int activeUsers = 0;
		for (int i = 0; i < users.size(); i++)
			if (users[i].IsActive())
				activeUsers++;

		//if no users left, break
		if(activeUsers == 0)
			return;

		//Get time quantum per user
		int timePerUser = timeQuantum / activeUsers;
		//create vector to pair active processes
		vector<pair<Process*, int> > processMap;
		pair<Process*, int> tmp;

		for (int i = 0; i < users.size(); i++)
		{
			Process* p = users[i].GetActiveProcesses();

			int timePerProcess = timePerUser / users[i].ActiveProcesses();

			for (int j = 0; j < users[i].ActiveProcesses(); j++)
			{
				//set the runtime of each Process
				p[j].setRunTime(timePerProcess);
			}

			tmp = make_pair(p,users[i].ActiveProcesses());
			processMap.push_back(tmp);
		}

		int tmpProcessSize = 0;

		for(int i = 0; i < processMap.size(); i++)
		{
			tmpProcessSize += get<1>(processMap[i]);
		}

		activeProcesses = new Process[tmpProcessSize];

		for(int i = 0; i < tmpProcessSize;)
		{
			for(int j = 0; j < processMap.size(); j++)
			{
				for(int k = 0; k < processMap[j].second; k++)
				{
					activeProcesses[i] = processMap[j].first[k];
					i++;
				}

			}
		}

		for(int i = 0; i < tmpProcessSize; i++)
		{
			if( i != 0 )
			{
				activeProcesses[i-1].Suspend();
				if(activeProcesses[i-1].getRemainingTime() == 0)
				{
					activeProcesses[i-1].Terminate();
				}
			}

			activeProcesses[i].Wake(currentTime, path);
			if(activeProcesses[i].getRunTime() >= activeProcesses[i].getRemainingTime())
			{
				Sleep(activeProcesses[i].getRemainingTime() * 1000);
				activeProcesses[i].setRemainingTime(0);
				currentTime += activeProcesses[i].getRemainingTime();
			}
			else
			{
				Sleep(activeProcesses[i].getRunTime() * 1000);
				activeProcesses[i].setRemainingTime(activeProcesses[i].getRemainingTime()-activeProcesses[i].getRunTime());
				currentTime += activeProcesses[i].getRunTime();
			}
		}

	}
}

thread Scheduler::RunThread(const char* path)
{
	return std::thread([=] { Run(path); });
}