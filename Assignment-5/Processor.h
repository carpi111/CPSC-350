#include <iostream>
#include "BST.h"
#include "GenStack.h"
#include "Menu.h"

using namespace std;

class Processor
{
    protected:
        //GenStack<BST<Student*> > masterStudentStack;
        //GenStack<BST<Faculty*> > masterFacultyStack;

    public:
        BST<Student> masterStudent;
        BST<Faculty> masterFaculty;

        Processor();
        ~Processor();

        void readFromFile();
        void writeToFile();

        void printMasterStudent(TreeNode<Student> *n);
        void printMasterFaculty(TreeNode<Faculty> *n);

        void outputMasterStudent(TreeNode<Student> *n, string s);
        void outputMasterFaculty(TreeNode<Faculty> *n, string s);

        void displayStudentInfo(int i);
        void displayFacultyInfo(int i);

        void addStudent();
        void addFaculty();

        void addStudentFromFile(int i, string n, string l, double g, string m, int a);
        void addFacultyFromFile(int i, string n, string l, string d);

        TreeNode<Student>* getMasterStudentRoot();
        TreeNode<Faculty>* getMasterFacultyRoot();

        int checkInput(int l, int u, string m);

        void saveTree(TreeNode<Student> *n);

        void run();
};
