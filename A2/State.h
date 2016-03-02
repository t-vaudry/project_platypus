#pragma once
#include <thread>
#include "IOManager.h"

class State
{
public:
    State();
    ~State();
    virtual void execute(void *, char, int) = 0;
};
