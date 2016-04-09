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