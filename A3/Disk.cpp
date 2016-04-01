#include "Disk.h"

Disk::Disk()
{
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

void Disk::add(int varID, int value)
{
	string page = to_string(varID) + ' ' + to_string(value);
	IOManager::getInstance()->write(page, 1);
}

void Disk::remove(int varID)
{
	IOManager::getInstance()->removeLine(varID);
}