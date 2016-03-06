#include "Terminated.h"

Terminated::Terminated()
{
}

Terminated::~Terminated()
{
}

void Terminated::execute(void * threadHandler)
{
	//Terminate the current process thread
	TerminateThread(threadHandler, 0);
}
