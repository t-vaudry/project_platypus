#pragma once
#include "State.h"
#include <Windows.h>

class Running :
    public State
{
public:
    Running();
    ~Running();
    void execute(void *);
};

