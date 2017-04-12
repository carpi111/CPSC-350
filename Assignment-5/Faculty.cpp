#include "Faculty.h"

using namespace std;

Faculty::Faculty(){};

Faculty::Faculty(int i, string n, string l, string d)
{
    id = i;
    name = n;
    level = l;
    department = d;
    adviseeIDArray = new int[4];
    numAdvisees = 0;
    maxArraySize = 4;

    for (int i = 0; i < 4; ++i)
    {
        adviseeIDArray[i] = -1;
    }
}

Faculty::~Faculty()
{
    delete [] adviseeIDArray;
};

void Faculty::printFaculty()
{
    cout << "Faculty ID: " << id << " | Name: " << name << " | Level: " << level << " | Dept: " << department << "\nAdvisee IDs: ";
    printAdvisees();
    cout << endl;
}

void Faculty::printAdvisees()
{
    if (numAdvisees == 0)
    {
        cout << "No Advisees";
    }

    // GO THROUGH ADVISEE LIST AND PRINT ID OF ALL
    else
    {
        for (int i = 0; i < maxArraySize; ++i)
        {
            if (adviseeIDArray[i] != -1)
            {
                cout << adviseeIDArray[i];

                if (i < numAdvisees - 1)
                {
                    cout << ", ";
                }
            }
        }
    }

    cout << endl;
}

void Faculty::addAdvisee(int aid)
{
    // IF ARRAY IS FULL, DOUBLE IN SIZE AND ADD ADVISEE
    if (numAdvisees == maxArraySize)
    {
		int *temp1 = new int[numAdvisees];

        // MAKE TEMP ARRAY OF SAME SIZE AS CURRENT ARRAY
		for (int i = 0; i < numAdvisees; ++i)
		{
			temp1[i] = adviseeIDArray[i];
		}

        // DOUBLES SIZE OF ARRAY
		adviseeIDArray = new int[numAdvisees * 2];

        maxArraySize = numAdvisees * 2;

        // REPOPULATE FIRST HALF WITH OLD VALUES
		for (int i = 0; i < numAdvisees; ++i)
		{
			adviseeIDArray[i] = temp1[i];
		}

        // POPULATE SECOND HALF WITH 'OPEN' STATUS
        for (int i = numAdvisees; i < numAdvisees * 2; ++i)
        {
            adviseeIDArray[i] = -1;
        }

        adviseeIDArray[++numAdvisees] = aid;
	}

    // IF ARRAY NOT FULL, ADD ADVISEE IN FIRST OPEN POSITION
    else
    {
        int f = 0;

        // CHECK IF STUDENT IS ALREADY BEING ADVISED BY THIS FACULTY MEMBER
        for (int i = 0; i < maxArraySize; ++i)
        {
            if (adviseeIDArray[i] == aid)
            {
                f = maxArraySize;
            }
        }

        // IF NOT, ADD THEM
        while (f < maxArraySize)
        {
            if (adviseeIDArray[f] == -1)
            {
                adviseeIDArray[f] = aid;

                ++numAdvisees;

                break;
            }

            ++f;
        }
    }
}

bool Faculty::removeAdvisee(int adviseeID)
{
    bool deleted = false;

    // GO THROUGH ADVISEE LIST; IF FOUND DELETE
    for (int i = 0; i < maxArraySize; ++i)
    {
        if (adviseeIDArray[i] == adviseeID)
        {
            adviseeIDArray[i] = -1;

            --numAdvisees;

            deleted = true;
        }
    }

    if (!deleted)
    {
        cout << "\nAdvisee not found." << endl;
    }

    return deleted;
}

int Faculty::getMaxArraySize()
{
    return maxArraySize;
}

string Faculty::getDepartment()
{
    return department;
}

int Faculty::getNumAdvisees()
{
    return numAdvisees;
}
