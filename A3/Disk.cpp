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

//A new value is written to the disk.
//The disk obtains the variable ID and value
//and writes to the disk.txt file
void Disk::add(int varID, int value)
{
	string page = to_string(varID) + ' ' + to_string(value);
	IOManager::getInstance()->write(page, 1);
}

//Searches for a variable ID on the disk
//If the variable ID is found, delete the
//line containing that ID and return the
//value that was stored there. Else, 
//return -1
int Disk::remove(int varID)
{
	int returnVal = -1;
	returnVal = IOManager::getInstance()->getValueFromDisk(varID);
	if (returnVal != -1)
		IOManager::getInstance()->removeLine(varID);
	return returnVal;
}