#include <iostream>
#include "Person.h"

using namespace std;

class Student : public Person
{
    public:
        double gpa;
        string major;
        int advisorID;

        Student();
        Student(int i, string n, string l, double g, string m, int a);
        ~Student();

        void setAdvisorID(int aid);

        void printStudent();

        double getGPA();
        string getMajor();
        int getAdvisorID();
};
