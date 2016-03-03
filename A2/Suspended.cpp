#include "Suspended.h"

Suspended::Suspended()
{
}

Suspended::~Suspended()
{
}

void Suspended::execute(void * threadHandler)
{
	SuspendThread(threadHandler);
}