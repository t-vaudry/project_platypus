#include "Running.h"

Running::Running()
{
}

Running::~Running()
{
}

void Running::execute(void * threadHandler)
{
	//Resume the execution of the current process thread
	ResumeThread(threadHandler);
}
