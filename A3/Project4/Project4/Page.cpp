#include "Page.h"

Page::Page()
{
	var = Variable();
}

Page::Page(Variable newVar)
{
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

int Page::getValue()
{
	return var.getValue();
}