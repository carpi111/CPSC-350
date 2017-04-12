#include "Student.h"

using namespace std;

Student::Student(){};

Student::Student(int i, string n, string l, double g, string m, int a)
{
    id = i;
    name = n;
    level = l;
    gpa = g;
    major = m;
    advisorID = a;
}

Student::~Student(){};

void Student::setAdvisorID(int aid)
{
    advisorID = aid;
}

int Student::getAdvisorID()
{
    return advisorID;
}

void Student::printStudent()
{
    cout << "Student ID: " << id << " | Name: " << name << " | Grade: " << level << " | GPA: " << gpa << " | Major: " << major << " | Advisor ID: ";

    if (advisorID == -1)
    {
        cout << "No Advisor" << endl;
    }

    else
    {
        cout << advisorID << endl;
    }
}

double Student::getGPA()
{
    return gpa;
}

string Student::getMajor()
{
    return major;
}
