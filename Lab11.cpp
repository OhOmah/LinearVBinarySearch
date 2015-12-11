//This program belongs to Omar 
//C.S. M10A Fall 2015 Sec. #71245
//Lab11: Search Benchmarks

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

//Function Prototypes
void PrintNameHeader();
void FillMainList(int list[]);
void FillTestArray(const int list[], int test[]);
void PrintArray(const int ary[], int size);
void SelectionSort(int list[], int size);
int LinearSearch(const int list[], int value, int& comps);
int BinarySearch(const int list[], int value, int& comps);
void ResultsLinear(int list[], int test[]);
void ResultsBinary(int list[], int test[]);


//Constants
const int MaxSize = 511;
const int MaxTest = 50;
const unsigned int Seed = 1785741;


int main()
{
	//Declarations
	char userImput;
	int List[MaxSize], Test[MaxTest];

	cout << setprecision(1) << fixed << showpoint;

	PrintNameHeader();

	cout << "Do you want to use random values? (y/n): ";
	cin >> userImput;
	cout << endl;
	if (userImput == 'y' || userImput == 'Y')
	{
		srand(static_cast<unsigned int>(time(0)));
	}
	else
	{
		srand(Seed);
	}
	
	cout << "\nOriginal Array: \n";

	FillMainList(List);
	PrintArray(List, MaxSize);

	cout << "\n\nTest Array: \n";

	FillTestArray(List, Test);
	PrintArray(Test, MaxTest);

	cout << "\nLinear Search without sorting: \n";
	ResultsLinear(List, Test);

	SelectionSort(List, MaxSize);
	cout << "\nArray Sorted: \n";
	PrintArray(List, MaxSize);

	cout << "\n\nLinear Search Post Selection Sort: \n";
	ResultsLinear(List, Test);

	cout << "\nBinary Search: \n";
	ResultsBinary(List, Test);

	return 0;
}


//Functions

void PrintNameHeader()
{
	cout << "*********************************" << endl;
	cout << "*              Omar             *" << endl;
	cout << "*       C.S. M10A Fall 2015     *" << endl;
	cout << "*    Lab11: Search Benchmarks   *" << endl;
	cout << "*     Due Date: Wed. Dec 16     *" << endl;
	cout << "*********************************" << endl;
	cout << endl;
}

//-----------------------------


void FillMainList(int list[])
{
	int num; 
	bool found;
	int index = 0;
	
	while (index < MaxSize)
	{
		num = rand() % 5000;
		found = false;
		for (int j = 0; j < index; j++)
		{
			if (num == list[j])
				found = true;
		}
		if (!found)
		{
			list[index] = num;
			index++;
		}
	}
}


//----------------------

void FillTestArray(const int list[], int test[])
{
	int indexplus = 0;
	int num = 0;
	for (int index = 0; index < MaxTest; index++)
	{
		test[index] = list[indexplus];
		indexplus += 12;
		if (indexplus > MaxSize)
		{
			num = rand() % 5000;
			test[index] = num;
		}
	}
}

//-----------------------

void PrintArray(const int ary[], int size)
{
	for (int index = 0; index < size; index++)
	{
		cout << setw(8) << ary[index];
	}
}

//----------------------

void SelectionSort(int list[], int size)
{
	int StartScan, MinIndex, MinValue;
	for (StartScan = 0; StartScan < size - 1; StartScan++)
	{
		MinIndex = StartScan;
		MinValue = list[StartScan];
		for (int index = StartScan + 1; index < size; index++)
		{
			if (list[index] < MinValue)
			{
				MinValue = list[index];
				MinIndex = index;
			}
		}
		list[MinIndex] = list[StartScan];
		list[StartScan] = MinValue;
	}
}

//-----------------------

int LinearSearch(const int list[], int value, int& comps)
{
	comps = 0;
	for (int index = 0; index < MaxSize; index++)
	{
		comps++;
		if (list[index] == value)
		{
			return index;
		}
	}

	return -1;
}

//--------------------

int BinarySearch(const int list[], int value, int& comps)
{
	int first = 0,
		last = MaxSize - 1,
		middle,
		position = -1;

	comps = 0;

	bool found = false;
	while (!found && first <= last)
	{
		comps++;
		middle = (first + last) / 2;
		if (list[middle] == value)
		{
			found = true;
			position = middle;
			return position;
		}
		else if (list[middle] > value)
			last = middle - 1;
		else
			first = middle + 1;
	}
	return -1;
}

//--------------------------

void ResultsLinear(int list[], int test[])
{
	int comps, value = 0;
	int search = 0;
	int average[MaxTest];
	double sum = 0;
	string found = "found",
		notFound = "NOT found",
		result = "UNKNOWN";

	cout << setw(15) <<  "Test Value" << setw(11) << "Result" << setw(20) << " # of Comparisons" << endl;
	for (int index = 0; index < MaxTest; index++)
	{
		value = test[index];

		search = LinearSearch(list, value, comps);
		average[index] = comps;
		if (search != -1)
		{
			result = found;
		}
		else
		{
			result = notFound;
		}
		cout << setw(10) << test[index] << setw(15) << result << setw(15) << comps << endl;
	}

	for (int j = 0; j < MaxTest; j++)
	{
		sum += average[j];
	}
	sum = sum / MaxTest;

	cout << "\nThe average number of comparisons is: " << sum << endl;
}

//--------------------------

void ResultsBinary(int list[], int test[])
{
	int comps, value = 0;
	int search = 0;
	int average[MaxTest];
	double sum = 0;
	string found = "found",
		notFound = "NOT found",
		result = notFound;

	cout << setw(15) << "Test Value" << setw(11) << "Result" << setw(20) << " # of Comparisons" << endl;
	for (int index = 0; index < MaxTest; index++)
	{
		value = test[index];

		search = BinarySearch(list, value, comps);
		average[index] = comps;
		if (search != -1)
		{
			result = found;
		}
		else
		{
			result = notFound;
		}
		cout << setw(10) << test[index] << setw(15) << result << setw(15) << comps << endl;
	}

	for (int j = 0; j < MaxTest; j++)
	{
		sum += average[j];
	}
	sum = sum / MaxTest;

	cout << "\nThe average number of comparisons is: " << sum << endl;
}
