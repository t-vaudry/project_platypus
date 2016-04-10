#include "ProcessManager.h"

//ProcessManager constructor. Obtains all processes
//from the process file. The processes are placed
//in a vector.
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

	string start;
	string end;

	for (int i = 0; i < numberOfProcesses; i++)
	{
		getline(processStream, start, ' ');
		getline(processStream, end);

		Process p; // same process p
		p.initialize(i + 1, stoi(start), stoi(end));
		processes.push_back(p);
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

//Starts the clock of all process threads.
//Terminates itself once all processes have
//been terminated.
void ProcessManager::run()
{
	for (int i = 0; i < processes.size(); i++)
	{
		processThreads.push_back(processes[i].startRunTime());
	}
	while (terminatedProcesses < numberOfProcesses);
	Clock::getInstance()->terminate();
	TerminateThread(handle, 0);
}

void ProcessManager::incrementTerminatedProcesses()
{
	terminatedProcesses++;
}