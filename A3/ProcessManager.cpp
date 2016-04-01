#include "ProcessManager.h"

ProcessManager::ProcessManager()
{
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
	return thread([=] { run(); });
}

void ProcessManager::run()
{
	while (true)
	{
		for (int i = 0; i < numberOfProcesses; i++)
		{
			if (processes[i].isStarted == false && Clock::getInstance()->getTime() >= processes[i].getStartTime())
			{
				processThreads.push_back(processes[i].startRunTime());
				processThreads.back().join();

				processThreads.push_back(processes[i].startThread());
				processThreads.back().join();
			}
		}
	}
}