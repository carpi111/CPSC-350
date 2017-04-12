#include <iostream>
#include <array>
#include "DLL.h"
#include "Person.h"

using namespace std;

class Faculty : public Person
{
    public:
        string department;
        unsigned int numAdvisees;
        unsigned int maxArraySize;
        int *adviseeIDArray;

        Faculty();
        Faculty(int i, string n, string l, string d);
        ~Faculty();

        void printFaculty();

        void printAdvisees();

        void addAdvisee(int aid);
        bool removeAdvisee(int adviseeID);

        int getMaxArraySize();

        string getDepartment();
        int getNumAdvisees();
};
