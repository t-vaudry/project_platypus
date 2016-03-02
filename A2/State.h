#pragma once
#include <thread>
#include "IOManager.h"

class State
{
public:
    State();
    ~State();
    virtual void execute(thread::native_handle_type&, char, int) = 0;
};
