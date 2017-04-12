#include <iostream>

using namespace std;

class Menu
{
    private:
        int response;
    public:
        Menu();
        ~Menu();

        void welcome();
        void displayMenu();
};
