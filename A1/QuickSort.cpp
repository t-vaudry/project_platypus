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
	thread t(QuickSort, elements, numberOfElements);
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
	//Index references to the current position in quicksort
	int leftIndex;
	int rightIndex;

	int pivot;

/***************************************************************************\
FOR QUICKSORT, IF SIZE OF ARRAY IS LESS THAN 3, PERFORM SIMPLE CHECK AND
SWAP IF NECESSARY. IF SIZE IS 1, RETURN THE 1 ELEMENT.
/***************************************************************************/

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

/***************************************************************************\
STARTING QUICKSORT, FIRST NEED IS THE PIVOT. USING THE MEDIAN OF THREE,
THE FUNCTION FindPivot FINDS THE PIVOT AND PLACES IT AT THE END OF THE ARRAY.
/***************************************************************************/

	pivot = FindPivot(arr, arrSize);

	leftIndex = 0;
	rightIndex = arrSize - 2;

/***************************************************************************\
AFTER DECLARING THE INITIAL INDICES OF OUR REFERENCES, THE QUICKSORT
ALGORITHM BEGINS TO PROCESS HERE. THE CONCEPT OF QUICKSORT IS TO PLACE THE
LARGER VALUES THAN THE PIVOT TO THE FAR RIGHT, AND THE SMALLER VALUES TO THE
FAR LEFT, UNTIL THE REFERENCE POINTERS CROSS OVER. ONCE THEY HAVE CROSSED
OVER, MOVE THE PIVOT IN BETWEEN THE REFENCE POINTS. SPLIT THE ARRAY INTO TWO
SUB-ARRAYS AND PERFORM QUICKSORT ON THEM.
/***************************************************************************/

	while (leftIndex <= rightIndex)
	{
		while (arr[leftIndex] <= pivot && leftIndex < arrSize -1)
		{
			//For as long as the left reference point is not past the end of the array
			//and the value at the reference point is less than the pivot continue
			//along the array.
			leftIndex++;
		}

		while (arr[rightIndex] > pivot && rightIndex > 0)
		{
			//For as long as the right reference point is not past the beginning of the array
			//and the value at the reference point is greater than the pivot continue
			//along the array.
			rightIndex--;
		}

		if (leftIndex < rightIndex)
		{
			//If the indices haven't crossed, swap the values and keep going.
			Swap(arr, leftIndex, rightIndex);

			leftIndex++;
			rightIndex--;
		}
		else if (leftIndex == 0 && rightIndex == 0)
		{
			//Case where the indices are both pointing at the beginning of the array.
			//Exit and continue to follow the steps
			break;
		}
		else if (leftIndex == arrSize - 1 && rightIndex == arrSize - 1)
		{
			//Case where the indices are both pointing at the end of the array.
			//Exit and continue to follow the steps
			break;
		}
	}

	Swap(arr, arrSize - 1, leftIndex);

	if (leftIndex == 0 && rightIndex == 0)
	{
		rightIndex--;
	}

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

/***************************************************************************\
USING THREADS TO SORT THE TWO SUB-ARRAYS WILL MAKE THE PROGRAM RUN FASTER.
TO ENSURE THAT THE FUNCTIONS DO NOT TRY TO MOVE BACK TO THE MAIN BEFORE THE
OTHER FINISHES, JOIN THE THREADS TO THE PROCESS.
/***************************************************************************/

	thread t1(QuickSort, leftArr, rightIndex + 1);
	thread t2(QuickSort, rightArr, arrSize - leftIndex - 1);
	
	t1.join();
	t2.join();

/***************************************************************************\
ONCE SORTING OF THE SUB-ARRAYS IS COMPLETE, PLACE THE SORT VALUES BACK INTO
THEIR ORIGINAL ARRAY, COMPLETELY SORTED.
/***************************************************************************/

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
