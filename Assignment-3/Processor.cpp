/* File Processing Class */

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "GenStack.h"
#include "Processor.h"

using namespace std;

// STACKS FOR STORING UNPAIRED CHARACTER
GenStack<char> bracketStack(4);
GenStack<char> curlyBraceStack(4);
GenStack<char> parenthesisStack(4);

// STACKS FOR STORING LINE NUMBER OF ERROR
GenStack<int> bracketLineNumberStack(4);
GenStack<int> curlyBraceLineNumberStack(4);
GenStack<int> parenthesisLineNumberStack(4);

Processor::Processor(){};

Processor::~Processor(){};

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

	string line;
	char character;
	int lengthOfLine;
	int lineNumber = 1;
	bool isStillErrorFree = true;

	// IF INPUT FILE OPENED, READ TO END OF FILE AND POPULATE DESIGNATED STACKS
	if (inputFile.is_open())
	{
   		while (getline(inputFile, line) && isStillErrorFree)
   		{
   			lengthOfLine = line.length();

   			for (int i = 0; i < lengthOfLine; ++i)
   			{
   				character = line[i];

   				// *** CHECKING IF CLOSING DELIMITER IS FOUND BEFORE OPENING DELIMITER *** //
   					// (MISSING OPENING DELIMITER)
   				switch (character)
				{
					// *** PARENTHESIS *** //
					case ('('):
					{
						parenthesisStack.push(line[i]);
   						parenthesisLineNumberStack.push(lineNumber);

						break;
					}

					// CHECK IF OPEN-PARENTHESIS WAS PREVIOUSLY FOUND; IF NOT, THROW ERROR
					case (')'):
					{
						if (parenthesisStack.isEmpty())
						{
							cout << "\nERROR - missing '(' on or before line: " << lineNumber << '\n' << endl;
							isStillErrorFree = false;
						}

						else
						{
							parenthesisStack.pop();
	   						parenthesisLineNumberStack.pop();
	   					}

						break;
					}

					// *** BRACKETS *** //
					case ('['):
					{
						bracketStack.push(line[i]);
   						bracketLineNumberStack.push(lineNumber);

						break;
					}

					// CHECK IF OPEN-BRACKET WAS PREVIOUSLY FOUND; IF NOT, THROW ERROR
					case (']'):
					{
						if (bracketStack.isEmpty())
						{
							cout << "\nERROR - missing '[' on or before line: " << lineNumber << '\n' << endl;
							isStillErrorFree = false;
						}

						else
						{
							bracketStack.pop();
	   						bracketLineNumberStack.pop();
	   					}

						break;
					}

					// *** CURLY BRACES *** //
					case ('{'):
					{
						curlyBraceStack.push(line[i]);
   						curlyBraceLineNumberStack.push(lineNumber);

						break;
					}

					// CHECK IF OPEN CURLY BRACE WAS PREVIOUSLY FOUND; IF NOT, THROW ERROR
					case ('}'):
					{
						if (curlyBraceStack.isEmpty())
						{
							cout << "\nERROR - missing '{' on or before line: " << lineNumber << '\n' << '\n' << endl;
							isStillErrorFree = false;
						}

						else
						{
							curlyBraceStack.pop();
	   						curlyBraceLineNumberStack.pop();
	   					}

						break;
					}

					// ANY OTHER CHARACTER
					default:
					{
						break;
					}
				}
   			}

   			++lineNumber;
	   	}

	   	// NO CLOSING DELIMITERS FOUND BEFORE AN OPENING DELIMITER WAS FOUND
	   		// (MISSING CLOSING DELIMITER)
	   	if (isStillErrorFree)
	   	{
			if (!parenthesisLineNumberStack.isEmpty())
			{
			 	cout << "\nERROR - missing ')' on or after line: " << parenthesisLineNumberStack.pop() << '\n' << endl;
			}

			else if (!bracketLineNumberStack.isEmpty())
			{
				cout << "\nERROR - missing ']' on or after line: " << bracketLineNumberStack.pop() << '\n' << endl;
			}

			else if (!curlyBraceLineNumberStack.isEmpty())
			{
				cout << "\nERROR - missing '}' on or after line: " << curlyBraceLineNumberStack.pop() << '\n' << endl;
			}
	   	}

	   	// NO ERRORS FOUND
   		if (isStillErrorFree && parenthesisStack.isEmpty() && bracketStack.isEmpty() && curlyBraceStack.isEmpty())
   		{
			cout << "\n* * * Congratulations! There were no errors found. * * *" << endl;
   		}
	}

	inputFile.close();
}

void Processor::refreshStacks()
{
	while (!bracketStack.isEmpty())
	{
		bracketStack.pop();
	}

	while (!bracketLineNumberStack.isEmpty())
	{
		bracketLineNumberStack.pop();
	}

	while (!curlyBraceStack.isEmpty())
	{
		curlyBraceStack.pop();
	}

	while (!curlyBraceLineNumberStack.isEmpty())
	{
		curlyBraceLineNumberStack.pop();
	}

	while (!parenthesisStack.isEmpty())
	{
		parenthesisStack.pop();
	}

	while (!parenthesisLineNumberStack.isEmpty())
	{
		parenthesisLineNumberStack.pop();
	}
}
