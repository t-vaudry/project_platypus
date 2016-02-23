#include "Running.h"


Running::Running()
{
	counter = 0;
}


Running::~Running()
{
}

void Running::execute(int time, char user, int process, const char* path)
{
	if (counter == 0)
	{
		IOManager IO;
		string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Resumed \n";
		IO.Write(line, path);
	}
	counter++;
	_sleep(1000);
}
