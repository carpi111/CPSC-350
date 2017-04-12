#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include "Processor.h"

using namespace std;

Processor::Processor()
{
    lineType = 1;
    studentEntryTime = 0;
    studentTimeAtWindow = 0;
    numStudentsAtClockTick = 0;

    medianArrayElementsCount = 0;
    idleArrayElementsCount = 0;

    totalNumWindows = 0;
    totalStudents = 0;

    showFileLoadingErrors = true;
    messageString = " minutes";
}

Processor::~Processor()
{
    delete [] windowArray;
    delete [] medianArray;
    delete [] idleArray;
}

// READS FILE AND SETS EVERYTHING UP
bool Processor::readFile(string f)
{
	ifstream inputFile;
	inputFile.open(f.c_str());
	string line;
    int lineNumber = 1;

	if (inputFile.is_open())
	{
        try
        {
            // FIRST LINE IS TOTAL NUMBER OF WINDOWS
       		getline(inputFile, line);
       		totalNumWindows = stoi(line);

            windowArray = new Student*[totalNumWindows];

            // MAKE ALL WINDOWS EMPTY
            for (int i = 0; i < totalNumWindows; ++i)
            {
                Student* stud = new Student();

                windowArray[i] = stud;
            }

            lineNumber++;
        }

        catch (exception e)
        {
            cout << "\nERROR ON LINE " << lineNumber << ": TOTAL NUMBER OF WINDOWS INCORRECT FORMAT\n" << endl;

            showFileLoadingErrors = false;

            return false;
        }

        while (getline(inputFile, line))
        {
            switch (lineType)
            {
                // CLOCK TICK
                case (1):
                {
                    try
                    {
                        // LINE WILL BE STUDENT ENTRY TIME
                   		studentEntryTime = stoi(line);

                        lineType++;
                        lineNumber++;
                    }

                    catch (exception e)
                    {
                        cout << "\nERROR ON LINE " << lineNumber << ": CLOCK TICK IS INCORRECT FORMAT\n" << endl;

                        showFileLoadingErrors = false;

                        return false;
                    }

                    break;
                }

                // NUMBER OF STUDENTS
                case (2):
                {
                    try
                    {
                        if (line != "")
                        {
                            // LINE WILL BE NUMBER OF STUDENTS
                       		numStudentsAtClockTick = stoi(line);

                            for (int i = 0; i < numStudentsAtClockTick; ++i)
                            {
                                getline(inputFile, line);
                                lineNumber++;

                                try
                                {
                                    studentTimeAtWindow = stoi(line);
                                }

                                catch(exception e)
                                {
                                    cout << "\nERROR ON LINE " << lineNumber << ": STUDENT TIME AT WINDOW INCORRECT FORMAT\n" << endl;

                                    showFileLoadingErrors = false;

                                    return false;
                                }

                                totalStudents++;

                                Student* stud = new Student(studentTimeAtWindow, studentEntryTime);

                                studentQueue.enqueue(stud);
                            }

                            // NEXT LINE WILL BE CLOCK TICK
                            lineType = 1;
                        }
                    }

                    catch (exception e)
                    {
                        cout << "\nERROR ON LINE " << lineNumber << ": NUM STUDENTS IS INCORRECT FORMAT\n" << endl;

                        showFileLoadingErrors = false;

                        return false;
                    }

                    break;
                }

                default:break;
            }
        }
	}

    // FILE DID NOT OPEN
    else
    {
        return false;
    }

    return true;
}

bool Processor::incrementAllTimes(int c)
{
    // WINDOW TIME AND IDLE TIME
    for (int i = 0; i < totalNumWindows; ++i)
    {
        if (windowArray[i]->timeAtWindow > 0)
        {
            // TIME THAT STUDENT NEEDS AT WINDOW DECREASES ONE MINUTE
            windowArray[i]->timeAtWindow--;
        }

        else
        {
            // IF WINDOW IS EMPTY, INCREASE IDLE TIME OF WINDOW (REPRESENTED BY LAST STUDENT AT WINDOW)
            windowArray[i]->idleTime++;
        }
    }

    if (!studentQueue.isEmpty())
    {
        // TIME IN QUEUE OF ALL PEOPLE IN LINE
        ListNode<Student*> *curr = studentQueue.front;

        while (curr != NULL)
        {
            if (curr->data->entryTime < c)
            {
                curr->data->timeInQueue += 1;
            }

            curr = curr->next;
        }
    }

    return true;
}

double Processor::calcMeanWait()
{
    ListNode<int> *curr = waitTimeStatsList.front;

    double meanWait = 0;
    int sum = 0;
    int count = 0;

    while (curr != NULL)
    {
        sum += curr->data;
        curr = curr->next;

        count++;
    }

    if (count == 0)
    {
        setMinutesMessage(0);

        return 0;
    }

    meanWait = double(sum) / double(count);

    setMinutesMessage(meanWait);

    return meanWait;
}

double Processor::calcMedianWait()
{
    ListNode<int> *curr = waitTimeStatsList.front;

    double medianWait = 0;
    medianArrayElementsCount = 0;

    // COUNTS ELEMENTS IN MEDIAN LIST
    while (curr != NULL)
    {
        curr = curr->next;

        medianArrayElementsCount++;
    }

    if (medianArrayElementsCount == 0)
    {
        setMinutesMessage(0);

        return 0;
    }

    else
    {
        medianArray = new int[medianArrayElementsCount];

        curr = waitTimeStatsList.front;

        // PUTS EVERYTHING INTO THE ARRAY
        for (int i = 0; i < medianArrayElementsCount; ++i)
        {
            medianArray[i] = curr->data;

            curr = curr->next;
        }

        // SORTS ELEMENTS IN ASCENDING ORDER
        sort(medianArray, medianArray + medianArrayElementsCount);

        // IF ODD NUMBER OF ELEMENTS, RETURN MIDDLE
        if (medianArrayElementsCount % 2 == 1)
        {
            double d = 0;
            int t = 0;

            t = (medianArrayElementsCount / 2) + 1;
            d = medianArray[t];

            setMinutesMessage(d);

            return d;
        }

        // IF EVEN NUMBER OF ELEMENTS, FIND AVERAGE OF MIDDLE TWO
        else
        {
            double d = 0;
            int t1 = 0;
            int t2 = 0;

            t1 = medianArrayElementsCount / 2;
            t2 = (medianArrayElementsCount / 2) + 1;

            if (medianArray[t2] == 0)
            {
                setMinutesMessage(0);

                return 0;
            }

            d = double(medianArray[t1]) / double(medianArray[t2]);

            setMinutesMessage(d);

            return d;
        }
    }
}

// RETURN LAST ELEMENT OF SORTED MEDIAN ARRAY
int Processor::calcLongestWait()
{
    if (medianArrayElementsCount != 0)
    {
        setMinutesMessage(medianArray[medianArrayElementsCount - 1]);

        return medianArray[medianArrayElementsCount - 1];
    }

    else
    {
        setMinutesMessage(0);

        return 0;
    }
}

// CHECK MEDIAN ARRAY FOR ANY VALUES OVER TEN
int Processor::calcNumWaitsOverTen()
{
    if (medianArrayElementsCount != 0)
    {
        int c = 0;

        for (int i = 0; i < medianArrayElementsCount; ++i)
        {
            if (medianArray[i] > 10)
            {
                ++c;
            }
        }

        setMinutesMessage(c);

        return c;
    }

    else
    {
        setMinutesMessage(0);

        return 0;
    }

}

double Processor::calcMeanIdle()
{
    ListNode<int> *curr = idleTimeStatsList.front;

    double meanIdle = 0;
    int sum = 0;
    int count = 0;

    while (curr != NULL)
    {
        sum += curr->data;
        curr = curr->next;

        count++;
    }

    if (count == 0)
    {
        setMinutesMessage(count);

        return 0;
    }

    meanIdle = double(sum) / double(count);

    setMinutesMessage(meanIdle);

    return meanIdle;
}

int Processor::calcLongestIdle()
{
    ListNode<int> *curr = idleTimeStatsList.front;

    idleArrayElementsCount = 0;

    // COUNTS ELEMENTS IN MEDIAN LIST
    while (curr != NULL)
    {
        curr = curr->next;

        idleArrayElementsCount++;
    }

    idleArray = new int[idleArrayElementsCount];

    curr = idleTimeStatsList.front;

    // PUTS EVERYTHING INTO THE ARRAY
    for (int i = 0; i < idleArrayElementsCount; ++i)
    {
        idleArray[i] = curr->data;

        curr = curr->next;
    }

    // SORTS ELEMENTS IN ASCENDING ORDER
    sort(idleArray, idleArray + idleArrayElementsCount);

    setMinutesMessage(idleArray[idleArrayElementsCount - 1]);

    return (idleArray[idleArrayElementsCount - 1]);
}

int Processor::calcNumIdleOverFive()
{
    int c = 0;

    for (int i = 0; i < idleArrayElementsCount; ++i)
    {
        if (idleArray[i] > 5)
        {
            ++c;
        }
    }

    setMinutesMessage(c);

    return c;
}

string Processor::getMinutesMessage()
{
    return messageString;
}

void Processor::setMinutesMessage(int t)
{
    if (t != 1)
    {
        messageString = " minutes";
    }

    else
    {
        messageString = " minute";
    }
}

string Processor::getStudentsMessage()
{
    if (totalStudents != 1)
    {
        return (" students were helped.\n\nStatistics");
    }

    else
    {
        return (" student was helped.\n\nStatistics");
    }
}
