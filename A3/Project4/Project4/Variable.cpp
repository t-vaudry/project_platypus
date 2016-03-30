#include "Variable.h"
#include "Clock.h"

Variable::Variable()
{
	ID = 0;
	value = 0;
	lastAccess = 0;
}

Variable::Variable(int id, int val, int time)
{
	ID = id;
	value = val;
	lastAccess = time;
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

void Variable::setLastAccess(int time)
{
	lastAccess = time;
}

int Variable::getLastAccess()
{
	return lastAccess;
}