#include "Disk.h"

Disk::Disk()
{
	//path = ;
}

Disk::~Disk()
{
}

Disk* Disk::instance;

Disk* Disk::getInstance()
{
	if (instance == NULL)
	{
		instance = new Disk();
	}
	return instance;
}