#pragma once
#include "IOManager.h"

class State
{
public:
    State();
    ~State();
    virtual void execute(void *) = 0;
};
