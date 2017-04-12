/* Registrar's Office */

#include <iostream>
#include "Processor.h"

using namespace std;

int main(int argc, char** argv)
{
    Processor p;

    int currentTime = 0;
    int openWindows = 0;

    bool stopRunning = false;

    // CHECK THAT THERE IS ONLY ONE COMMAND LINE ARGUMENT
	if (argc == 2)
	{
		// CHECK IF ARGUMENT IS VALID; IF SO, RUN PROGRAM
		if (p.readFile(argv[1]))
		{
            while (!stopRunning)
            {
                // IF NO ONE IN LINE AND NO ONE AT WINDOW, STOP RUNNING
                if (p.studentQueue.isEmpty())
                {
                    int t = 0;

                    for (int i = 0; i < p.totalNumWindows; ++i)
                    {
                        // WINDOW OPEN FOR STUDENT
                        if ((p.windowArray[i]->timeAtWindow) < 1)
                        {
                            t++;
                        }
                    }

                    if (t == p.totalNumWindows)
                    {
                        stopRunning = true;
                    }
                }

                // CHECK ALL WINDOWS; IF ONE IS OPEN, CHECK FIRST PERSON IN QUEUE AND SEND TO WINDOW IF THEIR ARRIVAL TIME IS VALID
                for (int i = 0; i < p.totalNumWindows; ++i)
                {
                    // WINDOW OPEN FOR STUDENT
                    if (p.windowArray[i]->timeAtWindow < 1)
                    {
                        // SOMEONE IN LINE
                        if (!p.studentQueue.isEmpty())
                        {
                            Student* s = p.studentQueue.getFront();

                            // STUDENT READY FOR WINDOW
                            if (s->entryTime <= currentTime)
                            {
                                // CHECK IDLE TIME OF WINDOW; IF NON-ZERO, ADD TO IDLE TIME STATS LIST
                                if (p.windowArray[i]->idleTime > 0)
                                {
                                    p.idleTimeStatsList.enqueue(p.windowArray[i]->idleTime);
                                }

                                // TAKES THEM OUT OF LINE AND PUTS THEM AT A WINDOW
                                p.windowArray[i] = p.studentQueue.dequeue();

                                // ADDS THEIR TIME SPENT IN LINE TO RUNNING STATS LIST
                                p.waitTimeStatsList.enqueue(p.windowArray[i]->timeInQueue);
                            }
                        }
                    }
                }

                // INCREMEMT ALL TIMES

                currentTime++;

                p.incrementAllTimes(currentTime);
            }

            // AFTER SIMULATION IS DONE, ACCOUNT FOR ANY IDLE WINDOWS THAT DID NOT HAVE A STUDENT IN THEM BY THE END
            for (int i = 0; i < p.totalNumWindows; ++i)
            {
                if (p.windowArray[i]->idleTime > 0)
                {
                    p.idleTimeStatsList.enqueue(p.windowArray[i]->idleTime);
                }
            }

            p.setMinutesMessage(currentTime);

            cout << "\nSimulation completed after " << currentTime << p.getMinutesMessage() << ". " << p.totalStudents << p.getStudentsMessage() << endl;

            cout << "Mean student wait time:    " << p.calcMeanWait() << p.getMinutesMessage() << endl;

            cout << "Median student wait time:  " << p.calcMedianWait() << p.getMinutesMessage() << endl;

            cout << "Longest student wait time: " << p.calcLongestWait() << p.getMinutesMessage() << endl;

            cout << "Waits over 10 minutes:     " << p.calcNumWaitsOverTen() << p.getMinutesMessage() << endl;

            cout << "Mean window idle time:     " << p.calcMeanIdle() << p.getMinutesMessage() << endl;

            cout << "Longest window idle time:  " << p.calcLongestIdle() << p.getMinutesMessage() << endl;

            cout << "Idle times over 5 minutes: " << p.calcNumIdleOverFive() << p.getMinutesMessage() << endl << endl;
		}

		// INVALID FILE NAME
		else
		{
            // ONLY PRINT THIS ERROR IF NOT ALREADY PRINTING AN ERROR FROM WITHIN THE FILE
            if (p.showFileLoadingErrors)
            {
                cout << "\n*** Error loading file: File does not exist in current directory. ***\n\n<<< Exiting Program >>>\n" << endl;
            }
		}
	}

	// ZERO OR MULTIPLE COMMAND LINE ARGUMENTS
	else
	{
		cout << "\n*** Please give a single file name in the command line. ***\n\n<<< Exiting Program >>>\n" << endl;
	}

	return 0;
}
