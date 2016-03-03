/*******************Programming Assignment 2******************/
/*****************YOU MUST EDIT THIS FILE*********************/
/********************Complete function nQueens****************/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

void permutation(vector<int>, int, int, ofstream&);
void swap(int *, int *);

void nQueens(int BoardSize, const char* path, int* currentTime) {

	if ((BoardSize!=2)||(BoardSize!=3)||(BoardSize!=0)){

	vector<int> a(BoardSize,0);

	for (int i=0; i<BoardSize; ++i)
		a[i] = i;

	ofstream outputFile;
	outputFile.open(path, ios_base::app);
	outputFile << BoardSize << endl;

	permutation(a, a[0], a.size(), outputFile);
	outputFile << "Completion Time: " << *currentTime << endl;
	outputFile.close();
	}

}

void permutation(vector<int> b, int current, int size, ofstream& outputFile){

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

	if(current == size-1)
	{
		int end_function = 0;

		for (int i=1; i<(size); ++i){
			for (int n=0; n<(size-i); ++n){

				if ((b[n]==(b[n+i]+i))||((b[n]+i)==b[n+i]))
					end_function = 1;
			}
		}

		if (end_function != 1){

			//solutions.push_back(b);
			for(int i=0; i<size; i++)
			{
				outputFile << b[i] << " ";
			}
			outputFile << endl;

		}
	}

	else
	{
		for(int i=current; i<size; i++)
		{
			int n = b[current];
			int m = b[i];

			swap(&n, &m);

			b[current] = n;
			b[i] = m;

			permutation(b, current+1, size, outputFile);

			swap(&n, &m);

			b[current] = n;
			b[i] = m;
		}
	}
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

