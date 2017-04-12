#include <iostream>
#ifndef included
#define included

using namespace std;

class Person
{
    public:
        int id;
        string name;
        string level;

        Person();
        ~Person();

        int getID();
        void setID(int v);

        string getName();
        string getLevel();
};

#endif
