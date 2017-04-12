#include "Processor.h"

using namespace std;

int main (int argc, char** argv)
{
    Processor p1;
    Menu menu;

    p1.readFromFile();

    menu.welcome();

    p1.run();

    p1.writeToFile();

    return 0;
}
