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

int Page::getValue()
{
	return var.getValue();
}

/*Variable Page::swap(Variable newVar)
{
	Variable tmp = var;
	var = newVar;
	return tmp;
}*/