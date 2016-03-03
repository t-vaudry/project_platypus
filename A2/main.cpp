#include <iostream>
#include "Scheduler.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //Ensure there is an input file
    try
    {
        if (argc < 1)
        {
            throw "No file path specified.\n";
        }
    }
    catch (char const* str)
    {
        cout << "Exception: " << str << endl;
    }

	//Create scheduler
    Scheduler* s = new Scheduler();
	
	//Call the Scheduler's run function with threads
    thread t;
    t = s->runThread(argv[1], argv[2], argv[3]);
    t.join();
}