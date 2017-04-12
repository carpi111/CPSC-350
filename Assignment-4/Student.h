#include <iostream>

class Student
{
    public:
        Student();
        ~Student();
        Student(int t, int e);

        int timeAtWindow;
        int entryTime;
        int timeInQueue;
        int idleTime; // THIS ONLY INCREMENTS WHEN THE STUDENT IS DONE AT A WINDOW
};
