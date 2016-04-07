#include "ProcessManager.h"

ProcessManager::ProcessManager()
{
	terminatedProcesses = 0;
	handle = NULL;

	string processString = IOManager::getInstance()->read(0);

	stringstream processStream; 
	processStream.str(processString);

	string numProcesses;
	getline(processStream, numProcesses);
	numberOfProcesses = stoi(numProcesses);

	processes = new Process[numberOfProcesses];

	string start;
	string end;

	for (int i = 0; i < numberOfProcesses; i++)
	{
		getline(processStream, start, ' ');
		getline(processStream, end);

		processes[i].initialize(i + 1, stoi(start), stoi(end));
	}
}

ProcessManager::~ProcessManager()
{
}

ProcessManager* ProcessManager::instance;

ProcessManager* ProcessManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new ProcessManager();
	}
	return instance;
}

thread ProcessManager::startThread()
{
	thread t = thread([=] { run(); });
	handle = t.native_handle();
	return t;
}

void ProcessManager::run()
{
	int remainingProcesses = numberOfProcesses;
	while (remainingProcesses > 0)
	{
		for (int i = 0; i < numberOfProcesses; i++)
		{
			if (processes[i].isStarted == false && Clock::getInstance()->getTime() >= processes[i].getStartTime())
			{
				processThreads.push_back(processes[i].startRunTime());
				//processThreads.back().join();

				processThreads.push_back(processes[i].startThread());
				//processThreads.back().join();

				string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(i + 1) + ": Started.";
				IOManager::getInstance()->write(output, 0);
				--remainingProcesses;
			}
		}
	}
	while (terminatedProcesses < numberOfProcesses);
	Clock::getInstance()->terminate();
	TerminateThread(handle, 0);
}

void ProcessManager::incrementTerminatedProcesses()
{
	terminatedProcesses++;
}