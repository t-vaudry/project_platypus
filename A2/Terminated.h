#pragma once
#include "State.h"
#include <Windows.h>

class Terminated :
    public State
{
public:
    Terminated();
    ~Terminated();
    void execute(void *);
};

