#include "Variable.h"

Variable::Variable()
{
	ID = -1;
	value = 0;
	lastAccess = 0;
}

Variable::Variable(int id, int val)
{
	ID = id;
	value = val;
	lastAccess = Clock::getInstance()->getTime();
}

Variable::~Variable()
{
}

void Variable::setID(int id)
{
	ID = id;
}

int Variable::getID()
{
	return ID;
}

void Variable::setValue(int val)
{
	value = val;
}

int Variable::getValue()
{
	return value;
}

void Variable::setLastAccess()
{
	lastAccess = Clock::getInstance()->getTime();
}

int Variable::getLastAccess()
{
	return lastAccess;
}