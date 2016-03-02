#include "Terminated.h"
#include <Windows.h>

Terminated::Terminated()
{
	counter = 0;
}


Terminated::~Terminated()
{
}

void Terminated::execute(thread::native_handle_type& threadHandler, char user, int ID)
{
	//if (counter == 0)
	//{
	//	IOManager IO;
	//	string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Finished \n";
	//	IO.Write(line, path);
	//}
	//counter++;
	TerminateThread(threadHandler, 0);
	//Sleep(1000);

}
