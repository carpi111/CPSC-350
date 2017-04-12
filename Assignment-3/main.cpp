/* Delimiter Parsing */

#include <iostream>
#include "GenStack.h"
#include "Processor.h"

using namespace std;

int main(int argc, char** argv)
{
	bool runProgram = true;

	Processor p;

	// CHECK THAT THERE IS ONLY ONE COMMAND LINE ARGUMENT
	if (argc == 2)
	{
		// CHECK IF ARGUMENT IS A FILE; IF SO, RUN PROGRAM
		if (p.setInputFile(argv[1]))
		{
			p.scanFile();

			while (runProgram)
			{
				cout << "\n\nWould you like to process another file?\n\n1 - Yes\n2 - No\n" << endl;

				string answer;
				cin >> answer;

				try
				{
					int intAnswer = stoi(answer);

					switch (intAnswer)
					{
						case (1):
						{
							cout << "\nEnter file name." << endl;

							string fileNameString;
							cin >> fileNameString;

							// EMPTY ALL STACKS BEFORE PROCESSING ANOTHER FILE
							p.refreshStacks();

							if (p.setInputFile(fileNameString))
							{
								p.scanFile();
							}

							else
							{
								cout << "\n*** File not found. Try again. ***" << endl;
							}

							break;
						}

						case (2):
						{
							cout << "\n<<< Exiting Program >>>\n" << endl;
							runProgram = false;
							break;
						}

						default:
						{
							cout << "\n*** Invalid answer. Try again. ***" << endl;
							break;
						}
					}
				}

				catch (exception e)
				{
					cout << "\n*** You did not enter a number! Try again. ***" << endl;
				}
			}
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
