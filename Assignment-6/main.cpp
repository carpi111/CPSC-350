/* Sorting Algorithms */

#include <iostream>
#include "Processor.h"

using namespace std;

int main(int argc, char** argv)
{
    Processor p;

    // CHECK THAT THERE IS ONLY ONE COMMAND LINE ARGUMENT
    if (argc == 2)
    {
        // CHECK IF ARGUMENT IS A FILE; IF SO, RUN PROGRAM
        if (p.setInputFile(argv[1]))
        {
            p.scanFile();
        }

        // INVALID FILE NAME
        else
        {
            cout << "\n*** Error loading file: File does not exist in current directory. ***\n\n<<< Exiting Program >>>\n" << endl;
        }
    }

    // ZERO OR MULTIPLE COMMAND LINE ARGUMENTS
    else
    {
        cout << "\n*** Please give a single file name in the command line. ***\n\n<<< Exiting Program >>>\n" << endl;
    }

    return 0;
}
