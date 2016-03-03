#include "Running.h"

Running::Running()
{
}

Running::~Running()
{
}

void Running::execute(void * threadHandler)
{
	ResumeThread(threadHandler);
}
