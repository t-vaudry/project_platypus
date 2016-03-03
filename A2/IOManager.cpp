#include "IOManager.h"

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

/*************************************************
The write function is used to write the log
information to the output file. The parameters are
a string, which is the log information, and the
path of the output file.
*************************************************/
void IOManager::write(string line, const char* path)
{
    //Open output file
    ofstream outputFile;
    outputFile.open(path, ios_base::app);

    try
    {
        if (!outputFile)
        {
            cout << "Unable to open file.\n";
            throw "No file found.";
        }
    }
    catch (char const* str)
    {
        cout << "Exception: " << str << endl;
    }

    outputFile << line;

    outputFile.close();

}

/*************************************************
The read function is used to read the information
from the input file. The parameter is the path of
the input file, and the function returns a string 
*************************************************/
string IOManager::read(const char* path)
{
    //Open input file
    ifstream inputFile;
    inputFile.open(path);

    try
    {
        if (!inputFile)
        {
            cout << "Unable to open file.\n";
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