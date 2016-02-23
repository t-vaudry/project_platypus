#include "Scheduler.h"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

Scheduler::Scheduler()
{
}

Scheduler::~Scheduler()
{
}

vector<User> Scheduler::GetUsers()
{
    return users;
}

void Scheduler::SetUsers(vector<User> newUsers)
{
    users = newUsers;
}

int Scheduler::GetTimeQuantum()
{
    return timeQuantum;
}

void Scheduler::SetTimeQuantum(int t)
{
    timeQuantum = t;
}

void Scheduler::Run(const char* path)
{
    string input;
    input = IO.Read(path);

    stringstream inputStream(input);

    //Parse input file
    //Get time quantum
    string timeQ;
    getline(inputStream, timeQ);
    timeQuantum = stoi(timeQ);

    int numInt;

    //Get users
    while (true)
    {
        //Get user name
        string n;
        getline(inputStream, n, ' ');

        if (n == "")
            break;

        //Get number of processes
        string num;
        getline(inputStream, num);
        numInt = stoi(num);

        //Create all processes
        Process* processes = new Process[numInt];
        for (int i = 0; i < numInt; i++)
        {
            string start;
            getline(inputStream, start, ' ');

            string service;
            getline(inputStream, service);

            Process p(stoi(start), stoi(service));

            processes[i] = p;
            //processes[i].join(); to do
        }

        //Create users
        User u(n, numInt, processes);
        users.push_back(u);
    }

    //Get number of active users
    int activeUsers = 0;
    for (int i = 0; i < users.size(); i++)
        if (users[i].IsActive())
            activeUsers++;

    //Get time quantum per user
    int timePerUser = timeQuantum / activeUsers;


    //Get number of active processes for each user
    for (int i = 0; i < users.size(); i++)
    {
        int timePerProcess = timePerUser / users[i].ActiveProcesses();

    }
}

thread Scheduler::RunThread(const char* path)
{
    return std::thread([=] { Run(path); });
}