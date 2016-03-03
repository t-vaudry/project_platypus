#include "Process.h"

using namespace std;

//Used to demonstrate the functionality of the code.
void nQueens(int, const char*, int*);

Process::Process()
{
	ReadyTime = 0;
	serviceTime = 0;
	remainingTime = 0;
	runTime = 0;
	ID = 0;
	user = NULL;
	state = new Inactive();
	threadHandler = NULL;
}

Process::Process(int Ready, int service, int id, char usr)
{
	ReadyTime = Ready;
	serviceTime = service;
	remainingTime = service;
	ID = id;
	user = usr;
	state = new Inactive();
	threadHandler = NULL;
}

Process::~Process()
{
}

int Process::getReadyTime()
{
	return ReadyTime;
}

void Process::setReadyTime(int time)
{
	ReadyTime = time;
}

int Process::getServiceTime()
{
	return serviceTime;
}

void Process::setServiceTime(int time)
{
	serviceTime = time;
}

int Process::getRemainingTime()
{
	return remainingTime;
}

void Process::setRemainingTime(int time)
{
	remainingTime = time;
}

int Process::getRunTime()
{
	return runTime;
}

void Process::setRunTime(int time)
{
	runTime = time;
}

int Process::getState()
{
	if (dynamic_cast<Ready*>(state))
		return 0;
	else if (dynamic_cast<Terminated*>(state))
		return 1;
	else if (dynamic_cast<Running*>(state))
		return 2;
	else if (dynamic_cast<Suspended*>(state))
		return 3;
	else //if (dynamic_cast<Inactive*>(state))
		return 4;
}

int Process::getID()
{
	return ID;
}

char Process::getUser()
{
	return user;
}

/***************************************************
The suspend function is used to suspend the process
during execution. The function sets the state of the
process to Suspended, executes the state function,
which will suspend the thread of the Process, and
then logs the information in the output file by use
of the IOManager.
***************************************************/
void Process::suspend(int& time, const char* path)
{
	IOManager IO;
	state = new Suspended();
	state->execute(threadHandler);
	string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(ID) + ", Paused \n";
	IO.write(line, path);
}

/***************************************************
The wake function is used to wake the process during
execution. The function sets the state of theprocess
to Running, executes the state function, which will
resume the thread of the Process, and then logs the
information in the output file by use of the
IOManager.
***************************************************/
void Process::wake(int& time, const char* path)
{
	IOManager IO;

	//If the process has not started, log that it is starting in the output file.
	if (dynamic_cast<Ready*>(state))
	{
		string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(ID) + ", Started \n";
		IO.write(line, path);
	}

	state = new Running();
	state->execute(threadHandler);
	string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(ID) + ", Resumed \n";
	IO.write(line, path);
}

/***************************************************
The activate function checks if the process is in
the Inactive state, and if so, puts it in the Ready
state.
***************************************************/
void Process::activate()
{
	if (dynamic_cast<Inactive*>(state))
	{
		state = new Ready();
	}
}

/***************************************************
The terminate function is used to terminate the 
process. The function sets the state of the process
to Terminated, executes the state function, which 
will terminate the thread of the Process, and then
logs the information in the output file by use of 
the IOManager.
***************************************************/
void Process::terminate(int& time, const char* path)
{
	IOManager IO;
	state = new Terminated();
	state->execute(threadHandler);
	string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(ID) + ", Finished \n";
	IO.write(line, path);
}

/*************************************************
The isActive function returns a boolean value to
indicate if a process is in neither Inactive or
Terminated.
*************************************************/
bool Process::isActive()
{
	if (getState() != 1 && getState() != 4)
		return true;
	else
		return false;
}

Process& Process::operator=(Process& p)
{
	ReadyTime = p.ReadyTime;
	serviceTime = p.serviceTime;
	remainingTime = p.remainingTime;
	runTime = p.runTime;
	state = p.state;
	user = p.user;
	ID = p.ID;
	threadHandler = p.threadHandler;
	
	return p;
}

/*************************************************
The run function is where the process executes its
code. In this case, the nQueens problem is solved.
Start by creating a new path which will allow for
multiple output files. Randomize the size of the
board to solve the puzzle and then call the 
function. This function is run on a thread, and
can be interrupted by the Scheduler.
*************************************************/
void Process::run(int* currentTime, const char* path)
{
	string new_path = path; 
	new_path.append( user + to_string(ID) + ".txt");
	path = new_path.c_str();
	srand(unsigned(time(NULL)));
	int size = rand()%1;
	size += 9;

	nQueens(size, path, currentTime);
}

/*************************************************
The runThread function is used to Run the member
function, run, of the Process in its own thread.
It also sets the threadHandler, so that it can be
used to Suspend, Resume and Terminate the thread.
*************************************************/
thread Process::runThread(int* currentTime, const char* path)
{
	thread t([&] {run(currentTime, path); });
	threadHandler = t.native_handle();
	return t;
}