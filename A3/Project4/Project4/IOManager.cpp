#include "IOManager.h"

IOManager::IOManager()
{
}

IOManager::~IOManager()
{
}

void IOManager::Write(string line, int mode)
{
	//Open input file
	ofstream outputFile;
	const char* path;

	if (mode == 0)
	{
		path = outputPath;
	}
	else
	{
		path = diskPath;
	}
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

string IOManager::Read(int mode)
{
	//Open input file
	ifstream inputFile;
	const char* path;

	if (mode == 0)
	{
		path = processPath;
	}
	else
	{
		path = memconfigPath;
	}
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