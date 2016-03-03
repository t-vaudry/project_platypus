#pragma once
#include "State.h"
#include <Windows.h>

class Suspended :
    public State
{
public:
    Suspended();
    ~Suspended();
    void execute(void *);
};


