#include "Process.h"
#include "MemoryManager.h" //Needs to be here and not in .h

using namespace std;

Process::Process()
{
	handle = NULL;
}

Process::Process(int id, int start, int end)
{
	ID = id;
	startTime = start;
	endTime = end;
	handle = NULL;
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
	startTime = t;
}

int Process::getStartTime()
{
	return startTime;
}

void Process::setEndTime(int t)
{
	endTime = t;
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
	int lineNumber;

	while (true)
	{
		//Select action at random (based on line number)
		lineNumber = rand() % numOfLines + 1;
		command = ioMan->readLineNumber(lineNumber);
		commandStream.str(command);

		//Parse instruction
		instruction = intParser->parse(commandStream);

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
		switch (instructionNumber)
		{
			case 1: //Store varID, value
				memMan->store(x1, x2);
				break;
			case 2: //Release varID
				memMan->release(x1);
				break;
			case 3: //Lookup varID
				memMan->lookup(x1);
				break;
			default:
				cout << "ERROR: Invalid instruction ID";
		}
	}
}

void Process::checkRunTime()
{
	while (!isStarted);
	while (Clock::getInstance()->getTime() < endTime*1000);
	terminateThread();
}