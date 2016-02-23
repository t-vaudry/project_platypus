#include "IOManager.h"

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

void IOManager::Write(string line, const char* path)
{
    //Open input file
    ofstream outputFile;
    outputFile.open(path);

    try
    {
        if (!outputFile)
        {
            cout << "Unable to open file.\n";
            system("pause");
            throw "No file found.";
        }
    }
    catch (char const* str)
    {
        cout << "Exception: " << str << endl;
    }

    outputFile << line << endl;

    outputFile.close();

}

string IOManager::Read(const char* path)
{
    //Open input file
    ifstream inputFile;
    inputFile.open(path);

    try
    {
        if (!inputFile)
        {
            cout << "Unable to open file.\n";
            system("pause");
            throw "No file found.";
        }
    }
    catch (char const* str)
    {
        cout << "Exception: " << str << endl;
    }


    string returnValue;
    while (!inputFile.eof())
    {
        string input;
        getline(inputFile, input);
        returnValue.append(input);
        returnValue.append("\n");
    }


    inputFile.close();

    return returnValue;
}