#include "Page.h"

Page::Page()
{
	var = Variable();
}

Page::Page(int newVarID, int newValue)
{
	Variable newVar = Variable(newVarID, newValue);
	var = newVar;
}

Page::~Page()
{
}

void Page::setVariable(Variable newVar)
{
	var = newVar;
}

Variable Page::getVariable()
{
	return var;
}

bool Page::empty()
{
	return (var.getID()==-1);
}

int Page::getValue()
{
	return var.getValue();
}