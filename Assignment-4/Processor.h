#include <string>
#include "Queue.h"
#include "Student.h"

using namespace std;

class Processor
{
    public:
        Processor();
        ~Processor();

        bool readFile(string f);
        bool incrementAllTimes(int c);

        double calcMeanWait();
        double calcMedianWait();
        int calcLongestWait();
        int calcNumWaitsOverTen();

        double calcMeanIdle();
        int calcLongestIdle();
        int calcNumIdleOverFive();

        string getMinutesMessage();
        void setMinutesMessage(int t);
        string getStudentsMessage();

        Student* *windowArray;

        Queue<Student*> studentQueue;

        Queue<int> waitTimeStatsList;
        Queue<int> idleTimeStatsList;

        int *medianArray;
        int *idleArray;

        int totalNumWindows;
        int totalStudents;

        bool showFileLoadingErrors;

    private:
        int lineType;
        int studentEntryTime;
        int studentTimeAtWindow;
        int numStudentsAtClockTick;
        int medianArrayElementsCount;
        int idleArrayElementsCount;
        string messageString;
};
