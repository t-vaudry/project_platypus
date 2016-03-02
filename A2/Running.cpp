#include "Running.h"
#include <Windows.h>
//#include <chrono>
//#include <thread>

Running::Running()
{
	counter = 0;
}


Running::~Running()
{
}

void Running::execute(thread::native_handle_type& threadHandler, char user, int ID)
{
	//if (counter == 0)
	//{
	//	IOManager IO;
	//	string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Resumed \n";
	//	IO.Write(line, path);
	//}
	//counter++;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	ResumeThread(threadHandler);
	//Sleep(1000);
}
