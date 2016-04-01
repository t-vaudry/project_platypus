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
	//while (true)
	//{
	//	for (int i; i < numberOfProcesses; i++)
	//	{
	//		if (processes[i].isStarted == false && Clock::getInstance().getTime() >= processes[i].getStartTime())
	//		{
	//			//Start thread
	//			//Flag process
	//		}
	//	}
	//}
}