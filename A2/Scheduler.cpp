#include "Scheduler.h"
#include <vector>
#include <string>
#include <sstream>

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

			Process p(stoi(start), stoi(service), i);

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
				userProcesses[j].Initiate(currentTime, users[i].GetName()[0], userProcesses[j].getID(), path);
		}
	}

	int numberOfFinishedUsers = 0;

	//Get number of active processes for each user
	while (numberOfFinishedUsers < users.size())
	{
		while(currentTime%timeQuantum != 0)
		{
			//foreach user. foreach process. if arrival time == current time, state = ready
			for (int i = 0; i < users.size(); i++)
			{
				Process* pList = users[i].GetAllProcesses();
				for (int j = 0; j < users[i].GetNumberOfProcesses(); j++)
				{
					if (pList[j].getReadyTime() == currentTime)
						pList[j].Activate();
				}
			}

			//Get number of active users
			int activeUsers = 0;
			for (int i = 0; i < users.size(); i++)
				if (users[i].IsActive())
					activeUsers++;

			//Get time quantum per user
			int timePerUser = timeQuantum / activeUsers;

			for (int i = 0; i < users.size(); i++)
			{
				if (users[i].Completed())
				{
					numberOfFinishedUsers++;
				}

				Process* p = users[i].GetActiveProcesses();

				for (int j = 0; j < users[i].ActiveProcesses(); j++)
				{
					int timePerProcess = timePerUser / users[i].ActiveProcesses();
				}


				//wait for time quantum
			}
		}
	}
}