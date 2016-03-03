#include "Terminated.h"

Terminated::Terminated()
{
}

Terminated::~Terminated()
{
}

void Terminated::execute(void * threadHandler)
{
	TerminateThread(threadHandler, 0);
}
