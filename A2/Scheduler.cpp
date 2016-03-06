#include "Scheduler.h"

using namespace std;

//Time begins at currentTime equals 1
Scheduler::Scheduler()
{
	currentTime = 1;
}

//All of the threads are joined to the main and scheduler thread in the destructor
Scheduler::~Scheduler()
{
	for(unsigned int i = 0; i < processThreads.size(); i++)
		processThreads[i].join();
}

vector<User> Scheduler::getUsers()
{
	return users;
}

void Scheduler::setUsers(vector<User> newUsers)
{
	users = newUsers;
}

int Scheduler::getTimeQuantum()
{
	return timeQuantum;
}

void Scheduler::setTimeQuantum(int t)
{
	timeQuantum = t;
}

/*************************************************
The run function executes all of the Scheduler's
process scheduling mechanism. Process, which are
run as threads, are given a fair share of time 
to execute until every process has completed.
*************************************************/
void Scheduler::run(const char* inputPath, const char* outputPath, const char* processOutputPath)
{
	string input;
	input = IO.read(inputPath);

	stringstream inputStream(input);

	//Parse input file
	//Get time quantum
	string timeQ;
	getline(inputStream, timeQ);
	timeQuantum = stoi(timeQ);

	int numberOfUsers;

	//While loop used to get the users from the input file.
	//Will then create the users processes and create user.
	while (true)
	{
		//Get user name
		string name;
		getline(inputStream, name, ' ');
		 
		//Condition for reaching last user
		if (name == "")
			break;

		//Get number of processes
		string numberOfProcesses;
		getline(inputStream, numberOfProcesses);
		numberOfUsers = stoi(numberOfProcesses);

		//Create all processes
		vector<Process*> processes;
		for(int i = 0; i < numberOfUsers; i++)
		{
			string start;
			getline(inputStream, start, ' ');

			string service;
			getline(inputStream, service);

			Process* new_process = new Process(stoi(start), stoi(service), i, name[0]);

			processes.push_back(new_process);
		}

		//Create users
		User usr(name, numberOfUsers, processes);
		users.push_back(usr);
	}

/*****************************************************************************
While loop to recalculate the time per user, time per process, and then execute
the Scheduler's fair-share algorithm.
******************************************************************************/
	while (true)
	{
		//For each user. For each process. If arrival time == current time, state = Ready
		for(unsigned int i = 0; i < users.size(); i++)
		{
			vector<Process*> processList;
			processList = users[i].getAllProcesses();

			for(int j = 0; j < users[i].getNumberOfProcesses(); j++)
			{
				if (processList[j]->getReadyTime() <= currentTime)
				{
					processList[j]->activate();
				}
			}
		}

		//Get number of active users
		int activeUsers = 0;
		for(unsigned int i = 0; i < users.size(); i++)
			if (users[i].isActive())
				activeUsers++;

		//If no users left, exit loop
		if(activeUsers == 0)
			break;

		//Get time quantum per user
		int timePerUser = timeQuantum / activeUsers;

		//Create new vectors of Processes for Active Process in this time quantum, and the user's processes
		vector<Process*> activeProcesses;
		vector<Process*> userProcesses;

		//Clear the vectors, so that on next pass, they do not still contain previous Processes.
		activeProcesses.clear();
		userProcesses.clear();

		//Calculate the runTime per process and set the value
		for(unsigned int i = 0; i < users.size(); i++)
		{
			userProcesses = users[i].getActiveProcesses();

			if (users[i].getNumberOfActiveProcesses() != 0)
			{
				int timePerProcess = timePerUser / users[i].getNumberOfActiveProcesses();

				for(unsigned int j = 0; j < userProcesses.size(); j++)
				{
					//Set the runTime of each Process
					userProcesses[j]->setRunTime(timePerProcess);

					//Push process back into the vector of active processes
					activeProcesses.push_back(userProcesses[j]);
				}
			}

		}

/****************************************************************************************************
Next for loop is the scheduler executing the fair-share scheduling. Each process has a runTime, which
is used to run the Process for its allotted time. First check to suspend the previous process. If the
remaining time of that process is zero, then terminate the process. Then check if that state of the
thread is ready, if it is, start the thread of execution of that process and push it back into the
vector of processThreads. Then wake the process for the currentTime. Then simply check if the process
will run for its runTime or its remainingTime, and Sleep the scheduler for that time. Increment the
currentTime of the Scheduler by the time slept, and set the remaining time of the Process. On the
last pass out of the loop, suspend the last process and terminate it if completed.
****************************************************************************************************/

		for(unsigned int i = 0; i < activeProcesses.size(); i++)
		{
			if( i != 0 )
			{
				activeProcesses[i-1]->suspend(currentTime, outputPath);
				if(activeProcesses[i-1]->getRemainingTime() == 0)
				{
					activeProcesses[i-1]->terminate(currentTime, outputPath);
				}
			}

			//From Ready to Running, start the thread, and begin the process.
			if (activeProcesses[i]->getState() == 0)
			{
				processThreads.push_back(activeProcesses[i]->runThread(&currentTime, processOutputPath));
			}

			activeProcesses[i]->wake(currentTime, outputPath);

			if(activeProcesses[i]->getRunTime() >= activeProcesses[i]->getRemainingTime())
			{
				Sleep(activeProcesses[i]->getRemainingTime() * 1000);
				currentTime += activeProcesses[i]->getRemainingTime();
				activeProcesses[i]->setRemainingTime(0);
			}
			else
			{
				Sleep(activeProcesses[i]->getRunTime() * 1000);
				activeProcesses[i]->setRemainingTime(activeProcesses[i]->getRemainingTime()-activeProcesses[i]->getRunTime());
				currentTime += activeProcesses[i]->getRunTime();
			}
		}

		activeProcesses[activeProcesses.size()-1]->suspend(currentTime, outputPath);
		if (activeProcesses[activeProcesses.size()-1]->getRemainingTime() == 0)
		{
			activeProcesses[activeProcesses.size()-1]->terminate(currentTime, outputPath);
		}
	}
}

/***************************************************************************************************
The runThread function is used to Run the member function, run, of the Scheduler in its own thread.
It passes the parameters necessary for the path to the input file, the output log file, and the path
of the outfile files generated by the Process' Run.
****************************************************************************************************/
thread Scheduler::runThread(const char* inputPath, const char* outputPath, const char* processOutputPath)
{
	return std::thread([=] { run(inputPath, outputPath, processOutputPath); });
}