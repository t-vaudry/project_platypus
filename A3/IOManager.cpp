#include "IOManager.h"

IOManager::IOManager()
{
	//processPath = process;
	//memconfigPath = memconfig;
	//outputPath = output;
	//diskPath = disk;
}

IOManager::~IOManager()
{
}

IOManager* IOManager::instance;

IOManager* IOManager::getInstance()
{
	if (instance == NULL)
	{
		instance = new IOManager();
	}
	return instance;
}

void IOManager::write(string line, int mode)
{
	m.lock();
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
	outputFile.open(path, ios_base::app);

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
	m.unlock();

}

string IOManager::read(int mode)
{
	//Open input file
	ifstream inputFile;
	const char* path;

	if (mode == 0)
	{
		path = processPath;
	}
	else if (mode == 1)
	{
		path = diskPath;
	}
	else if (mode == 2)
	{
		path = memconfigPath;
	}
	else
	{
		path = commandPath;
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

string IOManager::readLineNumber(int lineNumber)
{
	int currLine = 0;
	string returnString;
	ifstream commands;
	commands.open(commandPath);
	while (getline(commands, returnString))
	{
		currLine++;
		if (currLine == lineNumber)
			break;
	}
	return returnString; //WARNING: no check for validity of line number
}

void IOManager::removeLine(int varID)
{
	ifstream disk;
	disk.open(diskPath);

	ofstream tmp;
	tmp.open(tmpPath);

	string wanted = to_string(varID); //variable to delete
	string line; //current line
	string lineID; //varID of current line
	while (getline(disk, line))
	{
		getline(stringstream(line), lineID, ' ');
		//if varID of line is not the desired, add the line to the temp file
		if (lineID != wanted)
		{
			tmp << line << endl;
		}
	}

	disk.close();
	tmp.close();
	remove(diskPath);
	rename(tmpPath, diskPath); //replace disk file with temp file, which does not have undesired var
}

int IOManager::getNumberOfLines()
{
	int numOfLines = 0;
	string line;
	ifstream commands;
	commands.open(commandPath);
	while (getline(commands, line))
	{
		numOfLines++;
	}
	return numOfLines;
}

int IOManager::getValueFromDisk(int varID)
{
	ifstream disk;
	disk.open(diskPath);

	string varValString;
	int val;

	string wanted = to_string(varID); //variable to delete
	string line; //current line
	string lineID; //varID of current line
	while (getline(disk, line))
	{
		getline(stringstream(line), lineID, ' ');
		if (lineID == wanted)
		{
			getline(stringstream(line), varValString, ' ');
			val = stoi(varValString);
			break;
		}
	}
	disk.close();
	return val;
}