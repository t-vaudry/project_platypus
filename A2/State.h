#pragma once
#include "IOManager.h"

class State
{
public:
    State();
    ~State();
    virtual void execute(int&, char, int, const char*) = 0;
};
