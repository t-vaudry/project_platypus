#include "IOManager.h"

IOManager::IOManager()
{
	processPath = "C:/Users/anita/Desktop/Files/processes.txt";
	memconfigPath = "C:/Users/anita/Desktop/Files/memconfig.txt";
	outputPath = "C:/Users/anita/Desktop/Files/output.txt";
	diskPath = "C:/Users/anita/Desktop/Files/disk.txt";
	commandPath = "C:/Users/anita/Desktop/Files/commands.txt";
	tmpPath = "C:/Users/anita/Desktop/Files/tmp.txt";
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

//Writes to an output file. The output file to write to
//is specified in the mode input:
//0: output file
//1: disk file.
//Mutual exclusion is assured with a mutex.
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

//Reads from a file specified by the mode input.
//The modes correspond to:
//0: process file
//1: disk file
//2: memory config file
//3: command file
//This function returns the entire contents
//of the file
string IOManager::read(int mode)
{
	m.lock();
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
	m.unlock();

	return returnValue;
}

//Returns the content of the line specified by lineNumber
string IOManager::readLineNumber(int lineNumber)
{
	m.lock();
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
	m.unlock();
	return returnString; //WARNING: no check for validity of line number
}

//Removes a line from the disk. The line to
//remove is specified by the variable ID
void IOManager::removeLine(int varID)
{
	m.lock();
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
	m.unlock();
}

//Returns the number of lines of the command file
int IOManager::getNumberOfLines()
{
	m.lock();
	int numOfLines = 0;
	string line;
	ifstream commands;
	commands.open(commandPath);
	while (getline(commands, line))
	{
		numOfLines++;
	}
	m.unlock();
	return numOfLines;
}

//Searches for a vairable by variable ID and returns its value
//Returns -1 if the variable ID is not found
int IOManager::getValueFromDisk(int varID)
{
	m.lock();
	ifstream disk;
	disk.open(diskPath);

	string varValString;
	int val = -1;

	string wanted = to_string(varID); //variable to delete
	string line; //current line
	string lineID; //varID of current line
	while (getline(disk, line))
	{
		stringstream lineStream = stringstream(line);
		getline(lineStream, lineID, ' ');
		if (lineID == wanted)
		{
			getline(lineStream, varValString, ' ');
			val = stoi(varValString);
			break;
		}
	}
	disk.close();
	m.unlock();
	return val;
}

//Deletes the first line of a file
//This is used to remove commands from
//the command file as they are used.
void IOManager::deleteFirstLine()
{
	m.lock();
	ifstream commands;
	commands.open(commandPath);

	ofstream tmp;
	tmp.open(tmpPath);

	string line;

	getline(commands, line);
	while (getline(commands, line))
	{
		tmp << line << endl;
	}

	commands.close();
	tmp.close();
	remove(commandPath);
	rename(tmpPath, commandPath); //replace disk file with temp file, which does not have undesired var
	m.unlock();
}