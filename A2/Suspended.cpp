#include "Suspended.h"
#include <Windows.h>

Suspended::Suspended()
{
	counter = 0;
}


Suspended::~Suspended()
{
}

void Suspended::execute(int& time, char user, int process, const char* path)
{
	if (counter == 0)
	{
		IOManager IO;
		string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Paused \n";
		IO.Write(line, path);
	}
	counter++;
	Sleep(1000);
}