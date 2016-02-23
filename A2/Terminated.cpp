#include "Terminated.h"


Terminated::Terminated()
{
    counter = 0;
}


Terminated::~Terminated()
{
}

void Terminated::execute(int time, char user, int process, const char* path)
{
    if (counter == 0)
    {
        IOManager IO;
        string line = "Time " + to_string(time) + ", User " + user + ", Process " + to_string(process) + ", Finished \n";
        IO.Write(line, path);
    }
    counter++;

}
