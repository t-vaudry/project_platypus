#include "Process.h"
#include "ProcessManager.h"

using namespace std;

Process::Process()
{
	handle = NULL;
	isStarted = false;
}

Process::Process(int id, int start, int end)
{
	ID = id;
	startTime = start * 1000;
	endTime = (start + end) * 1000;
	handle = NULL;
	isStarted = false;
}

Process::~Process()
{
}

void Process::setID(int id)
{
	ID = id;
}

int Process::getID()
{
	return ID;
}

void Process::setStartTime(int t)
{
	startTime = t * 1000;
}

int Process::getStartTime()
{
	return startTime;
}

int Process::getEndTime()
{
	return endTime;
}

thread Process::startThread()
{
	thread t([&] { run(); });
	handle = t.native_handle();
	return t;
}

thread Process::startRunTime()
{
	return thread([=] { checkRunTime(); });
}

void Process::terminateThread()
{
	//to do if handle is NULL throw
	ProcessManager::getInstance()->incrementTerminatedProcesses();
	TerminateThread(handle, 0);
}

void Process::run()
{
	isStarted = true;

	string command;
	stringstream commandStream;
	ifstream commands;

	vector<int> instruction;
	int instructionNumber; //instruction code
	int x1; //instruction first param
	int x2; //instruction second param

	IOManager* ioMan = IOManager::getInstance();
	MemoryManager* memMan = MemoryManager::getInstance();
	InstructionParser* intParser = new InstructionParser();

	int numOfLines = ioMan->getNumberOfLines();

	while (true)
	{
		command = ioMan->readLineNumber(1);
		ioMan->deleteFirstLine();
		commandStream.clear();
		commandStream.str(command);

		//Parse instruction
		instruction = intParser->parse(commandStream);

		if (instruction.size() == 0)
		{
			break;
		}


		//Get instruction info
		instructionNumber = instruction[0];
		x1 = instruction[1];

		if (instructionNumber == 1)
		{
			x2 = instruction[2];
		}
		else
		{
			x2 = -1;
		}

		//Execute action
		string output;
		switch (instructionNumber)
		{
			case 1: //Store varID, value
				memMan->store(x1, x2);
				output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Store: Variable " + to_string(x1) + ", Value: " + to_string(x2);
				break;
			case 2: //Release varID
				memMan->release(x1);
				output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Release: Variable " + to_string(x1);
				break;
			case 3: //Lookup varID
				x2 = memMan->lookup(x1);
				output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Lookup: Variable " + to_string(x1) + ", Value: " + to_string(x2);
				break;
			default:
				cout << "ERROR: Invalid instruction ID";
		}
		IOManager::getInstance()->write(output, 0);
	}
}

void Process::checkRunTime()
{
	while (!isStarted);
	while (Clock::getInstance()->getTime() < endTime);
	string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Finished.";
	IOManager::getInstance()->write(output, 0);
	terminateThread();
}

void Process::initialize(int id, int start, int end)
{
	ID = id;
	startTime = start * 1000;
	endTime = (start + end) * 1000;
	handle = NULL;
}