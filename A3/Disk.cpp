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

int Disk::remove(int varID)
{
	int returnVal = -1;
	returnVal = IOManager::getInstance()->getValueFromDisk(varID);
	if (returnVal != -1)
		IOManager::getInstance()->removeLine(varID);
	return returnVal;
}