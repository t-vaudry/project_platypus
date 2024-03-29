#include "Process.h"
#include "ProcessManager.h"

using namespace std;

Process::Process()
{
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
	ProcessManager::getInstance()->incrementTerminatedProcesses();
	TerminateThread(handle, 0);
}

//Executes the process. The process obtains the next
//command from the command file and executes it, while
//it still has time to do so.
void Process::run()
{
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

	//while there is still time to execute
	while ((endTime - Clock::getInstance()->getTime())>1000)
	{
		command = ioMan->readLineNumber(1);
		ioMan->deleteFirstLine();
		commandStream.clear();
		commandStream.str(command);

		//Parse instruction
		instruction = intParser->parse(commandStream);

		if (instruction.size() == 0 || instruction[0] == 4)
		{
			break;
		}

		//Get instruction info
		instructionNumber = instruction[0];

		if (instructionNumber != 4) //if valid instruction
		{
			x1 = instruction[1];

			if (instructionNumber == 1)
			{
				x2 = instruction[2];
			}
			else
			{
				x2 = -1;
			}
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
				if (memMan->release(x1))
					output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Release: Variable " + to_string(x1);
				else
					output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Release: Variable " + to_string(x1) + " does not exist.";
				break;
			case 3: //Lookup varID
				x2 = memMan->lookup(x1);
				if (x2 != -1)
				{
					output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Lookup: Variable " + to_string(x1) + ", Value: " + to_string(x2);
				}
				else
				{
					output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Lookup: Variable " + to_string(x1) + " does not exist.";
				}
				break;
			default:
				output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Invalid Instruction.";
		}
		IOManager::getInstance()->write(output, 0);
	}
}

//Manages starting and stopping the process thread.
//The process is started when the current time has 
//passed the process start time. The process is
//terminated when the current time is greater
//than the end time.
void Process::checkRunTime()
{
	//while not started, busy wait
	while (Clock::getInstance()->getTime() < startTime);

	//start thread and write to output
	string output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Started.";
	IOManager::getInstance()->write(output, 0);
	thread t = startThread();

	//while not ended, busy wait
	while (Clock::getInstance()->getTime() < endTime);

	//stop thread and write to output
	output = "Clock: " + to_string(Clock::getInstance()->getTime()) + ", Process " + to_string(ID) + ": Finished.";
	IOManager::getInstance()->write(output, 0);
	t.join();
	terminateThread();
}

//Initialize the process with given values. The end time
//is determined to be the sum of the start time and
//the burst time.
void Process::initialize(int id, int start, int end)
{
	ID = id;
	startTime = start * 1000;
	endTime = (start + end) * 1000;
	handle = NULL;
}