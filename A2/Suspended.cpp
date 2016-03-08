#include "Suspended.h"

Suspended::Suspended()
{
}

Suspended::~Suspended()
{
}

void Suspended::execute(void * threadHandler)
{
	//Suspend the execution of the current process thread
	SuspendThread(threadHandler);
}
