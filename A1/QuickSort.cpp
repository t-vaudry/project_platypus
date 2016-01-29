#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

void QuickSort(int* &, int);
void Swap(int* &, int, int);
int FindPivot(int* &, int);

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
	
	//Open input file
	ifstream inputFile;
	inputFile.open(argv[1]);

	string numberOfElementsString;
	string elementString;

	if (!inputFile)
	{
		cout << "Unable to open file";
		return -1;
	}
	
	//Get number of elements to sort
	getline(inputFile, numberOfElementsString);
	int numberOfElements = stoi(numberOfElementsString);

	//Create array for elements
	int* elements = new int[numberOfElements];

	//Fill array with unsorted elements
	for (int i = 0; i < numberOfElements; i++)
	{
		getline(inputFile, elementString);
		elements[i] = stoi(elementString);
	}

	inputFile.close();

	//Open output file
	ofstream outputFile;
	outputFile.open(argv[2]);

	//Call quicksort using a thread
	thread t(QuickSort,elements, numberOfElements);
	t.join();

	//Fill output file with sorted elements
	for (int i = 0; i < numberOfElements; i++)
	{
		outputFile << elements[i] << endl;
	}

	return 0;
}

void QuickSort(int* &arr, int arrSize)
{
	int leftIndex;
	int rightIndex;

	int pivot;

	if (arrSize < 3)
	{
		if (arrSize == 1)
		{
			return;
		}
		else
		{
			if (arr[0] > arr[1])
			{
				Swap(arr, 0, 1);
			}
			return;
		}
	}

	pivot = FindPivot(arr, arrSize);

	leftIndex = 0;
	rightIndex = arrSize - 2;

	while (leftIndex <= rightIndex)
	{
		while (arr[leftIndex] <= pivot && leftIndex < arrSize -1)
		{
			leftIndex++;
		}

		while (arr[rightIndex] > pivot && rightIndex > 0)
		{
			rightIndex--;
		}

		if (leftIndex < rightIndex)
		{
			Swap(arr, leftIndex, rightIndex);

			leftIndex++;
			rightIndex--;
		}
		else if (leftIndex == 0 && rightIndex == 0)
		{
			break;
		}
		else if (leftIndex == arrSize - 1 && rightIndex == arrSize - 1)
		{
			break;
		}
	}

	Swap(arr, arrSize - 1, leftIndex);

	if (leftIndex == 0 && rightIndex == 0)
		rightIndex--;

	//Create two subarrays
	int* leftArr = new int[rightIndex + 1];
	int* rightArr = new int[arrSize - leftIndex - 1];

	//Fill subarrays
	for (int i = 0; i < rightIndex + 1; i++)
	{
		leftArr[i] = arr[i];
	}
	for (int i = 0; i < arrSize - leftIndex - 1; i++)
	{
		rightArr[i] = arr[i + leftIndex + 1];
	}

	thread t1(QuickSort,leftArr, rightIndex + 1);
	thread t2(QuickSort,rightArr, arrSize - leftIndex - 1);
	
	t1.join();
	t2.join();

	int arrIndex = 0;
	
	for (int j = 0; j < rightIndex + 1; j++)
	{
		arr[arrIndex] = leftArr[j];
		arrIndex++;
	}

	arr[arrIndex] = pivot;
	arrIndex++;

	for (int j = 0; j < arrSize - leftIndex - 1; j++)
	{
		arr[arrIndex] = rightArr[j];
		arrIndex++;
	}
	
	//Create 2 threads
	//Call quicksort on both threads

	return;
}

void Swap(int* &arr, int idx1, int idx2)
{
	int tmp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = tmp;
}

int FindPivot(int* &arr, int arrSize)
{
	//Find pivot (median of three)
	int element0 = arr[0];
	int element1 = arr[1];
	int element2 = arr[2];

	int pivot;

	//Find median
	if (((element0 > element1) && (element0 < element2)) || ((element0 < element1) && (element0 > element2)))
	{
		pivot = element0;

		//Place pivot at end
		Swap(arr, 0, arrSize - 1);
	}
	else if (((element1 > element0) && (element1 < element2)) || ((element1 < element0) && (element1 > element2)))
	{
		pivot = element1;

		//Place pivot at end
		Swap(arr, 1, arrSize - 1);
	}
	else
	{
		pivot = element2;

		//Place pivot at end
		Swap(arr, 2, arrSize - 1);
	}
	return pivot;
}
