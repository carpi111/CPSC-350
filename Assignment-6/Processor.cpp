#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Processor.h"

using namespace std;

Processor::Processor(){};

Processor::~Processor()
{
    delete [] quickSortArray;
    delete [] insertSortArray;
    delete [] gnomeSortArray;
}

bool Processor::setInputFile(string name)
{
	ifstream fileTest;
	fileTest.open(name.c_str());

	if (fileTest.is_open())
	{
		cout << "\nFile \"" << name.c_str() << "\" was loaded." << endl;
		fileTest.close();
		fileName = name;

		return true;
	}

	else
	{
		return false;
	}
}

void Processor::scanFile()
{
    ifstream inputFile;
    inputFile.open(fileName.c_str());

    string numElementsString;
    string line;
    double value;
    int lineNumber = 1;

    getline(inputFile, numElementsString);

    try
    {
        numElements = stoi(numElementsString);
    }

    catch(exception e)
    {
        cout << "\n*** Error reading file: Incorrect format on line " << lineNumber << " ***\n" << endl;
        return;
    }

    quickSortArray = new double[numElements];
    insertSortArray = new double[numElements];
    gnomeSortArray = new double[numElements];

    // POPULATE ARRAYS
    for (int i = 0; i < numElements; ++i)
    {
        lineNumber++;

        getline(inputFile, line);

        try
        {
            // CONVERT LINE FROM FILE TO A DOUBLE
            value = stod(line);
        }

        catch(exception e)
        {
            cout << "\n*** Error reading file: Incorrect format on line " << lineNumber << " ***\n" << endl;
            return;
        }

        quickSortArray[i] = value;
        insertSortArray[i] = value;
        gnomeSortArray[i] = value;
    }

    inputFile.close();

    sortAll();
}

void Processor::quickSort(double array[], int left, int right)
{
    int index = partition(array, left, right);

    // SORT LEFT HALF
    if (left < index - 1)
    {
        quickSort(array, left, index - 1);
    }

    // SORT RIGHT HALF
    if (index < right)
    {
        quickSort(array, index, right);
    }
}

int Processor::partition(double array[], int left, int right)
{
    // CHOOSE MIDDLE VALUE AS PIVOT
    int pivot = array[(left + right) / 2];

    while (left <= right)
    {
        // FIND ELEMENTS ON LEFT THAT BELONG ON RIGHT
        while (array[left] < pivot)
        {
            left++;
        }

        // FIND ELEMENT ON RIGHT THAT BELONGS ON LEFT
        while (array[right] > pivot)
        {
            right--;
        }

        // SWAP ELEMENTS AND MOVE LEFT & RIGHT INDICES
        if (left <= right)
        {
            swap(array, left, right);

            left++;
            right--;
        }
    }

    return left;
}

void Processor::insertionSort(double array[])
{
    for (int j = 1; j < numElements; ++j) // MARKER
    {
        double temp = array[j]; // STORE MARKED ITEM
        int k = j; // WHERE TO START SHIFTING

        while (k > 0 && array[k-1] >= temp) // WHILE ELEMENT TO LEFT IS LARGER, SHIFT
        {
            array[k] = array[k-1];
            --k;
        }

        array[k] = temp; // PLACE MARKED ITEM IN CORRECT SPOT
    }
}

void Processor::gnomeSort(double array[])
{
    int i = 0;

    while (i < numElements)
    {
        if (i == 0 || array[i-1] <= array[i]) // IF ELEMENT TO LEFT OF I IS SMALLER, KEEP MOVING RIGHT
        {
            ++i;
        }

        else // OTHERWISE, SWAP
        {
            double temp = array[i];
            array[i] = array[i-1];
            array[--i] = temp;
        }
    }
}

void Processor::sortAll()
{
    clock_t timeStart;
    clock_t timeEnd;

    cout << "\n     - SORTING -\n* ----------------- *\n";

    // - QUICK SORT - //
    timeStart = clock();
    quickSort(quickSortArray, 0, numElements - 1);
    timeEnd = clock();

    printf("\nQuickSort took %.2fms to sort %d numbers.\n", (float(timeEnd - timeStart)/CLOCKS_PER_SEC) * 1000, numElements);

    // - INSERTION SORT - //
    timeStart = clock();
    insertionSort(insertSortArray);
    timeEnd = clock();

    printf("\nInsertionSort took %.2fms to sort %d numbers.\n", (float(timeEnd - timeStart)/CLOCKS_PER_SEC) * 1000, numElements);

    // - GNOME SORT - //
    timeStart = clock();
    gnomeSort(gnomeSortArray);
    timeEnd = clock();

    printf("\nGnomeSort took %.2fms to sort %d numbers.\n\n", (float(timeEnd - timeStart)/CLOCKS_PER_SEC) * 1000, numElements);
}

bool Processor::isSorted(double array[])
{
    for (int i = 0; i < numElements - 1; ++i)
    {
        if (array[i] > array[i+1])
        {
            return false;
        }
    }

    return true;
}

void Processor::swap(double array[], int a, int b)
{
    double temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

string Processor::getFileName()
{
    return fileName;
}
