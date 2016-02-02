#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>

using namespace std;

void QuickSort(int* &, int);
void Swap(int* &, int, int);
void FindPivot(int* &, int, int&);

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
		cout << "Unable to open file.\n";
		system("pause");
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

	//Close input file
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

/***************************************************************************\
QUICKSORT SORTS AN ARRAY THROUGH A SERIES OF COMPARISONS
/***************************************************************************/
void QuickSort(int* &arr, int arrSize)
{
	//Index of elements to compare
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

	FindPivot(arr, arrSize, pivot);

	leftIndex = 0;
	rightIndex = arrSize - 2;

	/***************************************************************************\
	AFTER DECLARING THE INITIAL INDICES OF OUR REFERENCES, THE QUICKSORT
	ALGORITHM BEGINS TO PROCESS HERE. THE CONCEPT OF QUICKSORT IS TO PLACE
	VALUES LARGER THAN THE PIVOT TO THE FAR RIGHT, AND VALUES SMALLER THAN IT TO 
	THE FAR LEFT, UNTIL THE LEFT AND RIGHT INDICES CROSS OVER. ONCE THEY HAVE 
	CROSSED OVER, SWAP THE PIVOT WITH THE ELEMENT AT THE LEFT INDEX. SPLIT THE 
	ARRAY INTO TWO SUB-ARRAYS AND PERFORM QUICKSORT ON THEM.
	/***************************************************************************/

	while (leftIndex <= rightIndex)
	{
		//Move left pivot along until end of array or value is larger than pivot
		while (arr[leftIndex] <= pivot && leftIndex < arrSize - 1)
		{
			leftIndex++;
		}

		//Move right pivot along until beginning of array or value is smaller than pivot
		while (arr[rightIndex] > pivot && rightIndex > 0)
		{
			rightIndex--;
		}

		//If the indices haven't crossed, swap the left and right values and continue
		if (leftIndex < rightIndex)
		{
			Swap(arr, leftIndex, rightIndex);

			leftIndex++;
			rightIndex--;
		}
		//If both indices are at the beginning of the array, exit loop
		else if (leftIndex == 0 && rightIndex == 0)
		{
			break;
		}
		//If both indices are at the end of the array, exit loop
		else if (leftIndex == arrSize - 1 && rightIndex == arrSize - 1)
		{
			break;
		}
	}

	//Once all elements have been rearranged, swap pivot into place
	Swap(arr, arrSize - 1, leftIndex);

	//If pivot is at first position, decrement rightIndex to create a left array of size 0
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
	CREATE TWO THREADS TO RECURSIVELY SORT THE LEFT AND RIGHT SUBARRAYS.
	TO ENSURE THAT THE FUNCTIONS DO NOT TRY TO MOVE BACK TO THE MAIN BEFORE THE
	OTHER FINISHES, JOIN THE THREADS TO THE MAIN PROCESS.
	/***************************************************************************/

	thread leftThread(QuickSort, leftArr, rightIndex + 1);
	thread rightThread(QuickSort, rightArr, arrSize - leftIndex - 1);

	leftThread.join();
	rightThread.join();

	/***************************************************************************\
	ONCE SORTING OF THE SUB-ARRAYS IS COMPLETE, PLACE THE SORTED VALUES BACK INTO
	THEIR ORIGINAL ARRAY.
	/***************************************************************************/

	int arrIndex = 0;

	//Fill in left half of array
	for (int j = 0; j < rightIndex + 1; j++)
	{
		arr[arrIndex] = leftArr[j];
		arrIndex++;
	}

	//Place pivot
	arr[arrIndex] = pivot;
	arrIndex++;

	//Fill right half of array
	for (int j = 0; j < arrSize - leftIndex - 1; j++)
	{
		arr[arrIndex] = rightArr[j];
		arrIndex++;
	}

	return;
}

/***************************************************************************\
SWAP TAKES A REFERENCE TO AN ARRAY AND TWO INDICES AND SWAPS THE ELEMENTS
/***************************************************************************/
void Swap(int* &arr, int idx1, int idx2)
{
	int tmp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = tmp;
}

/***************************************************************************\
FINDPIVOT RETURNS THE VALUE OF THE MEDIAN OF THREE OF THE FIRST THREE 
ELEMENTS OF THE ARRAY. IT PLACES THE PIVOT FOUND THIS WAY TO THE END POSITION
/***************************************************************************/
void FindPivot(int* &arr, int arrSize, int& pivot)
{
	//Find median

	if (((arr[0] > arr[1]) && (arr[0] < arr[2])) || ((arr[0] < arr[1]) && (arr[0] > arr[2])))
	{
		pivot = arr[0];

		//Place pivot at end
		Swap(arr, 0, arrSize - 1);
	}
	else if (((arr[1] > arr[0]) && (arr[1] < arr[2])) || ((arr[1] < arr[0]) && (arr[1] > arr[2])))
	{
		pivot = arr[1];

		//Place pivot at end
		Swap(arr, 1, arrSize - 1);
	}
	else
	{
		pivot = arr[2];

		//Place pivot at end
		Swap(arr, 2, arrSize - 1);
	}
}
