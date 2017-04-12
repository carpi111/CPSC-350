/* DNA Sequence Statistics */

#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
	bool runProgram = true;

	// CREATE FILE vincecarpino.txt IF NONEXISTENT; IF EXISTS, OVERWRITE DATA
	ofstream fileWriter1("vincecarpino.out", ios::trunc);

	// WRITE INFO TO TOP OF vincecarpino.txt FILE
	fileWriter1 << "Vince Carpino\nID: 2260921\nAssignment 1 - DNA Sequence Statistics\n\n--------------------\n";

	fileWriter1.close();

	string fileName = argv[1];

	while(runProgram)
	{
		// CREATES ifstream OBJECT FOR READING FROM FILE AND OPENS 'fileName'
		ifstream fileReader(fileName.c_str());

		// APPEND STATS TO vincecarpino.txt FILE
		ofstream fileWriter2("vincecarpino.out", ios::app);


		string lineFromFile = "";

		int lineNumbers = 0;

		double countNumberOfA = 0;

		double countNumberOfC = 0;

		double countNumberOfT = 0;

		double countNumberOfG = 0;

		double totalSum = 0;

		///* COUNT NUCLEOTIDES AND CALCULATE SUM *///

		// ITERATE THROUGH EACH LINE OF THE FILE
		while(getline(fileReader, lineFromFile))
		{
			// FOR EACH LINE, ITERATE THROUGH EACH CHARACTER
			for(int i = 0; i < lineFromFile.length(); ++i)
			{
				switch(toupper(lineFromFile[i]))
				{
					case('A'):
					{
						countNumberOfA++;
						totalSum++;
						break;
					}

					case('C'):
					{
						countNumberOfC++;
						totalSum++;
						break;
					}

					case('T'):
					{
						countNumberOfT++;
						totalSum++;
						break;
					}

					case('G'):
					{
						countNumberOfG++;
						totalSum++;
						break;
					}
				}
			}

			lineNumbers++;
		}

		fileReader.close();


		///* CALCULATE MEAN AND RE-OPEN FILE TO CALCULATE VARIANCE *///

		int meanLength = totalSum / lineNumbers;

		int variance = 0;

		fileReader.open(fileName);

		// ITERATE THROUGH EACH LINE OF THE FILE AGAIN
		while(getline(fileReader, lineFromFile))
		{
			// pow() WAS GIVING ME WEIRD NUMBERS
			variance += (meanLength - lineFromFile.length()) * (meanLength - lineFromFile.length());
		}

		variance /= lineNumbers;

		// CALCULATE STANDARD DEVIATION
		int standardDeviation = sqrt(variance);


		fileWriter2 << "\nSum: " << totalSum << "\nMean: " << meanLength << "\nVariance: " << variance << "\nStandard Deviation: " << standardDeviation << endl << endl;


		// COMPUTE RELATIVE PROBABILITY OF EACH NUCLEOTIDE
		double relativeProbabilityOfA = countNumberOfA / totalSum;
		double relativeProbabilityOfC = countNumberOfC / totalSum;
		double relativeProbabilityOfT = countNumberOfT / totalSum;
		double relativeProbabilityOfG = countNumberOfG / totalSum;

		fileWriter2 << "Relative Probability:\nA: " << relativeProbabilityOfA << "%\nC: " << relativeProbabilityOfC << "%\nT: " << relativeProbabilityOfT << "%\nG: " << relativeProbabilityOfG << "%\n" << endl;

		fileReader.close();


		// NUCLEOTIDE BIGRAMS AND BIGRAM SUM
		double countNumberOfAA = 0;
		double countNumberOfAC = 0;
		double countNumberOfAT = 0;
		double countNumberOfAG = 0;

		double countNumberOfCA = 0;
		double countNumberOfCC = 0;
		double countNumberOfCT = 0;
		double countNumberOfCG = 0;

		double countNumberOfTA = 0;
		double countNumberOfTC = 0;
		double countNumberOfTT = 0;
		double countNumberOfTG = 0;

		double countNumberOfGA = 0;
		double countNumberOfGC = 0;
		double countNumberOfGT = 0;
		double countNumberOfGG = 0;

		double bigramSum = 0;


		///* RE-OPEN FILE TO COUNT BIGRAMS *///

		fileReader.open(fileName);

		// ITERATE THROUGH EACH LINE OF THE FILE
		while(getline(fileReader, lineFromFile))
		{
			// FOR EACH LINE, ITERATE THROUGH EACH CHARACTER
			for(int i = 0; i < lineFromFile.length(); ++i)
			{
				switch(toupper(lineFromFile[i]))
				{
					case('A'):
					{
						// AA
						if(toupper(lineFromFile[i+1]) == 'A')
						{
							countNumberOfAA++;
							bigramSum++;
						}

						// AC
						else if(toupper(lineFromFile[i+1]) == 'C')
						{
							countNumberOfAC++;
							bigramSum++;
						}

						// AT
						else if(toupper(lineFromFile[i+1]) == 'T')
						{
							countNumberOfAT++;
							bigramSum++;
						}

						// AG
						else if(toupper(lineFromFile[i+1]) == 'G')
						{
							countNumberOfAG++;
							bigramSum++;
						}

						break;
					}

					case('C'):
					{
						// CA
						if(toupper(lineFromFile[i+1]) == 'A')
						{
							countNumberOfCA++;
							bigramSum++;
						}

						// CC
						else if(toupper(lineFromFile[i+1]) == 'C')
						{
							countNumberOfCC++;
							bigramSum++;
						}

						// CT
						else if(toupper(lineFromFile[i+1]) == 'T')
						{
							countNumberOfCT++;
							bigramSum++;
						}

						// CG
						else if(toupper(lineFromFile[i+1]) == 'G')
						{
							countNumberOfCG++;
							bigramSum++;
						}
						
						break;
					}

					case('T'):
					{
						// TA
						if(toupper(lineFromFile[i+1]) == 'A')
						{
							countNumberOfTA++;
							bigramSum++;
						}

						// TC
						else if(toupper(lineFromFile[i+1]) == 'C')
						{
							countNumberOfTC++;
							bigramSum++;
						}

						// TT
						else if(toupper(lineFromFile[i+1]) == 'T')
						{
							countNumberOfTT++;
							bigramSum++;
						}

						// TG
						else if(toupper(lineFromFile[i+1]) == 'G')
						{
							countNumberOfTG++;
							bigramSum++;
						}
						
						break;
					}

					case('G'):
					{
						// GA
						if(toupper(lineFromFile[i+1]) == 'A')
						{
							countNumberOfGA++;
							bigramSum++;
						}

						// GC
						else if(toupper(lineFromFile[i+1]) == 'C')
						{
							countNumberOfGC++;
							bigramSum++;
						}

						// GT
						else if(toupper(lineFromFile[i+1]) == 'T')
						{
							countNumberOfGT++;
							bigramSum++;
						}

						// GG
						else if(toupper(lineFromFile[i+1]) == 'G')
						{
							countNumberOfGG++;
							bigramSum++;
						}
						
						break;
					}
				}
			}
		}

		///* COMPUTE RELATIVE PROBABILITY OF EACH NUCLEOTIDE BIGRAM *///

		double relativeProbabilityOfAA = countNumberOfAA / bigramSum;
		double relativeProbabilityOfAC = countNumberOfAC / bigramSum;
		double relativeProbabilityOfAT = countNumberOfAT / bigramSum;
		double relativeProbabilityOfAG = countNumberOfAG / bigramSum;

		double relativeProbabilityOfCA = countNumberOfCA / bigramSum;
		double relativeProbabilityOfCC = countNumberOfCC / bigramSum;
		double relativeProbabilityOfCT = countNumberOfCT / bigramSum;
		double relativeProbabilityOfCG = countNumberOfCG / bigramSum;

		double relativeProbabilityOfTA = countNumberOfTA / bigramSum;
		double relativeProbabilityOfTC = countNumberOfTC / bigramSum;
		double relativeProbabilityOfTT = countNumberOfTT / bigramSum;
		double relativeProbabilityOfTG = countNumberOfTG / bigramSum;

		double relativeProbabilityOfGA = countNumberOfGA / bigramSum;
		double relativeProbabilityOfGC = countNumberOfGC / bigramSum;
		double relativeProbabilityOfGT = countNumberOfGT / bigramSum;
		double relativeProbabilityOfGG = countNumberOfGG / bigramSum;


		fileWriter2 << "Nucleotide Bigram Probability:\nAA: " << relativeProbabilityOfAA << "%\nAC: " << relativeProbabilityOfAC << "%\nAT: " << relativeProbabilityOfAT << "%\nAG: " << relativeProbabilityOfAG << "%\n\nCA: " << relativeProbabilityOfCA << "%\nCC: " << relativeProbabilityOfCC << "%\nCT: " << relativeProbabilityOfCT << "%\nCG: " << relativeProbabilityOfCG << "%\n\nTA: " << relativeProbabilityOfTA << "%\nTC: " << relativeProbabilityOfTC << "%\nTT: " << relativeProbabilityOfTT << "%\nTG: " << relativeProbabilityOfTG << "%\n\nGA: " << relativeProbabilityOfGA << "%\nGC: " << relativeProbabilityOfGC << "%\nGT: " << relativeProbabilityOfGT << "%\nGG: " << relativeProbabilityOfGG << "%\n" << "\n--------------------\n" << endl;


		///* GENERATING 1000 DNA STRINGS *///

	    double standardGaussian;
	    int lengthOfStrings;
	    double random1;
	    double random2;
	    double random3;

		for(int i = 0; i < 1000; ++i)
		{
			// RESET GAUSSIAN EACH TIME
			standardGaussian = 0;

			// GENERATE RANDOM NUMBERS BETWEEN 0 AND 1
			random1 = double(rand()) / double(RAND_MAX);
			random2 = double(rand()) / double(RAND_MAX);

			// COMPUTE C VALUE
			standardGaussian = sqrt((-2) * log(random1)) * cos(2 * M_PI * random2);

			// COMPUTE RANDOM LENGTH
			lengthOfStrings = (standardDeviation * standardGaussian) + meanLength;

			// RESET DNA STRING EACH TIME
			string randomString = "";

			for(int j = 0; j < lengthOfStrings; ++j)
			{
				random3 = double(rand()) / double(RAND_MAX);

				if(random3 < relativeProbabilityOfA)
				{
					randomString.push_back('A');
				}

				else if(random3 < (relativeProbabilityOfA + relativeProbabilityOfC))
				{
					randomString.push_back('C');
				}

				else if(random3 < (relativeProbabilityOfA + relativeProbabilityOfC + relativeProbabilityOfT))
				{
					randomString.push_back('T');
				}

				else
				{
					randomString.push_back('G');
				}
			}

			fileWriter2 << randomString << endl << endl;
		}


		fileWriter2 << "--------------------\n";


		fileWriter2.close();

		cout << "\nStats were written.\n";


		///* OPTION FOR PROCESSING ANOTHER FILE *///

		cout << "\n\nWould you like to process another file?\n1 - Yes\n2 - No\n\n";

		int continueRunningInt;

		cin >> continueRunningInt;

		switch(continueRunningInt)
		{
			case(1):
			{
				cout << "Enter file name:\n";
				cin >> fileName;
				break;
			}

			case(2):
			{
				cout << "\nSee ya!\n";
				runProgram = false;
				break;
			}

			default:
			{
				cout << "\nInvalid entry. You lost your chance. Bye!\n";
				runProgram = false;
				break;
			}
		}
	}

	return 0;
}
