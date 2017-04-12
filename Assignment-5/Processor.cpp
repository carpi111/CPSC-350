#include <string>
#include <fstream>
#include "Processor.h"

using namespace std;

Processor::Processor(){};
Processor::~Processor(){};

void Processor::readFromFile()
{
    ifstream masterStudentFile;
    ifstream masterFacultyFile;

    // READING STUDENT FILE

    int i = 0;
    string n = "";
    string l = "";
    double g = 0;
    string m = "";
    int a = -1;

    string line;
    int numStudents = 0;
    int lineCount = 1;

	masterStudentFile.open("studentTable.txt");

    if (masterStudentFile.is_open())
    {
        try
        {
            // FIRST LINE IS TOTAL NUMBER OF STUDENTS
       		getline(masterStudentFile, line);

            if (line != "")
            {
                numStudents = stoi(line);
            }
        }

        catch (exception e)
        {
            cout << "\nINCORRECT FILE FORMAT\n" << endl;
        }

        // EACH BLOCK OF 7 LINES IS A NEW STUDENT; AFTER 7 LINES, CREATE STUDENT OBJECT (CASE 7)
        for (int j = 0; j < (7 * numStudents); ++j)
        {
            getline(masterStudentFile, line);

            switch (lineCount)
            {
                case 1:
                {
                    if (line != "--")
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    break;
                }

                case 2:
                {
                    try
                    {
                   		i = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    break;
                }

                case 3:
                {
                    n = line;

                    break;
                }

                case 4:
                {
                    l = line;

                    break;
                }

                case 5:
                {
                    try
                    {
                   		g = stod(line);
                    }

                    catch (exception e)
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    break;
                }

                case 6:
                {
                    m = line;

                    break;
                }

                // CREATE NODE FROM STUDENT OBJECT & INSERT NODE INTO MASTER STUDENT TREE
                case 7:
                {
                    try
                    {
                   		a = stoi(line);

                        Student *stud = new Student(i, n, l, g, m, a);

                        TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

                        masterStudent.insert(studNode);
                    }

                    catch (exception e)
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }
                    break;
                }

                default:break;
            }

            ++lineCount;

            if (lineCount > 7)
            {
                lineCount = 1;
            }
        }
    }

    else
    {
        cout << "\nSTUDENT TABLE NOT FOUND. STARTING APPLICATION WITH NO STUDENTS IN DATABASE." << endl;
    }

    masterStudentFile.close();

    // READING FACULTY FILE

    int numFaculty = 0;

    int fi = 0;
    string fn = "";
    string fl = "";
    string fd = "";
    int advID = 0;

    lineCount = 1;
    int createdCount = 0;

    int na = 0;

    masterFacultyFile.open("facultyTable.txt");

    if (masterFacultyFile.is_open())
    {
        try
        {
            // FIRST LINE IS TOTAL NUMBER OF FACULTY MEMBERS
       		getline(masterFacultyFile, line);

            if (line != "")
            {
                numFaculty = stoi(line);
            }
        }

        catch (exception e)
        {
            cout << "\nINCORRECT FILE FORMAT\n" << endl;
        }

        // READ THROUGH REST OF FILE AND CREATE A FACULTY OBJECT FOR EACH BLOCK OF INFO
        while (getline(masterFacultyFile, line))
        {
            switch (lineCount)
            {
                case 1:
                {
                    if (line != "--")
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    break;
                }

                case 2:
                {
                    try
                    {
                   		fi = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    break;
                }

                case 3:
                {
                    fn = line;

                    break;
                }

                case 4:
                {
                    fl = line;

                    break;
                }

                case 5:
                {
                    fd = line;

                    break;
                }

                // READ NUMBER OF ADVISEES & TAKE NEXT BLOCK AS THE ADVISEE IDS
                case 6:
                {
                    try
                    {
                   		na = stoi(line);
                    }

                    catch (exception e)
                    {
                        cout << "\nINCORRECT FILE FORMAT\n" << endl;
                    }

                    Faculty *fac = new Faculty(fi, fn, fl, fd);

                    createdCount++;

                    for (int k = 0; k < na; ++k)
                    {
                        getline(masterFacultyFile, line);

                        try
                        {
                       		advID = stoi(line);
                        }

                        catch (exception e)
                        {
                            cout << "\nINCORRECT FILE FORMAT\n" << endl;
                        }

                        fac->addAdvisee(advID);
                    }

                    // CREATE FACULTY NODE AND INSERT INTO MASTER FACULTY TREE
                    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, fi);

                    masterFaculty.insert(facNode);

                    break;
                }

                default:break;
            }

            ++lineCount;

            if (createdCount == numFaculty)
            {
                break;
            }

            if (lineCount > 6)
            {
                lineCount = 1;
            }
        }
    }

    else
    {
        cout << "\nFACULTY TABLE NOT FOUND. STARTING APPLICATION WITH NO FACULTY MEMBERS IN DATABASE." << endl;
    }

    masterFacultyFile.close();
}

void Processor::writeToFile()
{
    // STUDENT TREE
    ofstream masterStudentFile;
    ofstream masterFacultyFile;

    masterStudentFile.open("studentTable.txt");

    // RECURSIVELY OUTPUT MASTER STUDENT TO STUDENT TABLE FILE
    if (masterStudentFile.is_open())
    {
        masterStudentFile << masterStudent.getSize() << endl;

        TreeNode<Student> *n = masterStudent.getRoot();

        outputMasterStudent(n, "studentTable.txt");
    }

    masterStudentFile.close();

    // FACULTY TREE

    masterFacultyFile.open("facultyTable.txt");

    // RECURSIVELY OUTPUT MASTER FACULTY TO FACULTY TABLE FILE
    if (masterFacultyFile.is_open())
    {
        masterFacultyFile << masterFaculty.getSize() << endl;

        TreeNode<Faculty> *n = masterFaculty.getRoot();

        outputMasterFaculty(n, "facultyTable.txt");
    }

    masterFacultyFile.close();

    cout << "--- DATABASE WRITTEN TO FILES ---" << endl;
}

// RECURSIVE PRINT FUNCTION FOR MASTER STUDENT TREE (TAKES IN ROOT)
void Processor::printMasterStudent(TreeNode<Student> *n)
{
    if (n != NULL)
    {
        if (n->left != NULL)
        {
            printMasterStudent(n->left);
        }

        n->data->printStudent();

        if (n->right != NULL)
        {
            printMasterStudent(n->right);
        }
    }

    else
    {
        cout << ">> Student tree is empty <<" << endl;
    }
}

// RECURSIVE PRINT FUNCTION FOR MASTER FACULTY TREE (TAKES IN ROOT)
void Processor::printMasterFaculty(TreeNode<Faculty> *n)
{
    if (n != NULL)
    {
        if (n->left != NULL)
        {
            printMasterFaculty(n->left);
        }

        n->data->printFaculty();

        if (n->right != NULL)
        {
            printMasterFaculty(n->right);
        }
    }

    else
    {
        cout << ">> Faculty tree is empty <<" << endl;
    }
}

// RECURSIVE OUTPUT FUNCTION FOR MASTER STUDENT TREE (TAKES IN ROOT & FILE NAME)
void Processor::outputMasterStudent(TreeNode<Student> *n, string s)
{
    ofstream f;
    f.open(s, true);

    if (n != NULL)
    {
        f << "--\n";

        // OUTPUTS FACULTY MEMBER INFO TO FILE
        f << n->data->getID() << "\n" << n->data->getName() << "\n" << n->data->getLevel() << "\n" << n->data->getGPA() << "\n" << n->data->getMajor() << "\n" << n->data->getAdvisorID() << endl;

        if (n->left != NULL)
        {
            outputMasterStudent(n->left, s);
        }

        if (n->right != NULL)
        {
            outputMasterStudent(n->right, s);
        }
    }

    f.close();
}

// RECURSIVE OUTPUT FUNCTION FOR MASTER FACULTY TREE (TAKES IN ROOT & FILE NAME)
void Processor::outputMasterFaculty(TreeNode<Faculty> *n, string s)
{
    ofstream f;
    f.open(s, true);

    if (n != NULL)
    {
        f << "--\n";

        // OUTPUTS FACULTY MEMBER INFO TO FILE
        f << n->data->getID() << "\n" << n->data->getName() << "\n" << n->data->getLevel() << "\n" << n->data->getDepartment() << endl;

        // OUTPUTS NUMBER OF ADVISEE IDS
        f << n->data->getNumAdvisees() << "\n";

        // OUTPUTS ARRAY TO FILE
        if (n->data->getNumAdvisees() > 0)
        {
            for (int i = 0; i < n->data->maxArraySize; ++i)
            {
                // CHECKS ADVISEE ARRAY FOR ADVISEES; OUTPUTS ALL NON-EMPTY SPOTS (-1 MEANS EMPTY)
                if (n->data->adviseeIDArray[i] != -1)
                {
                    f << n->data->adviseeIDArray[i] << endl;
                }
            }
        }

        if (n->left != NULL)
        {
            outputMasterFaculty(n->left, s);
        }

        if (n->right != NULL)
        {
            outputMasterFaculty(n->right, s);
        }
    }

    else
    {
        cout << ">> Faculty tree is empty <<" << endl;
    }

    f.close();
}

// PROMPTS FOR STUDENT INFO, CREATES STUDENT OBJECT, CREATES STUDENT NODE, INSERTS NODE INTO MASTER STUDENT
void Processor::addStudent()
{
    cout << "\n--- ADDING NEW STUDENT ---\n" << endl;

    int i;
    string n;
    string l;
    double g;
    string m;
    int a;

    int answerInt = 0;
    double answerDbl = 0;
    string answer = "";

    while (true)
    {
        cout << "\nID of student: ";

        answerInt = 0;
        answer = "";
        cin >> answer;

        try
        {
            i = stoi(answer);

            // STUDENT ID IS POSITIVE AND STUDENT DOES NOT EXIST IN STUDENT TREE
            if (i > 0)
            {
                if (!masterStudent.isInTree(i))
                {
                    break;
                }

                else
                {
                    cout << "\nStudent already exists. Try another." << endl;
                }
            }

            else
            {
                cout << "\nInvalid input. Try again." << endl;
            }
        }

        catch (exception e)
        {
            cout << "\nInvalid input. Try again." << endl;
        }
    }

    string line;

    cout << "\nName of student: ";
    cin.ignore();
    getline(cin, n);

    cout << "\nGrade: ";
    getline(cin, l);

    while (true)
    {
        cout << "\nGPA: ";

        answerDbl = 0;
        answer = "";
        cin >> answer;

        try
        {
            g = stod(answer);

            if (g > 0 && g < 5)
            {
                break;
            }

            else
            {
                cout << "\nPlease enter a GPA between 0 and 5." << endl;
            }
        }

        catch (exception e)
        {
            cout << "\nInvalid input. Try again." << endl;
        }
    }

    cout << "\nMajor: ";
    cin.ignore();
    getline(cin, m);

    // IF IT IS POSSIBLE FOR THEM TO HAVE AN ADVISOR, PROMPT ACCORDINGLY
    if (!masterFaculty.isEmpty())
    {
        cout << "\nDoes this student have an advisor?\n1 - Yes\n2 - No" << endl;

        while (true)
        {
            answerInt = 0;
            answer = "";
            cin >> answer;

            try
            {
                answerInt = stoi(answer);

                if (answerInt == 1 || answerInt == 2)
                {
                    break;
                }
            }

            catch (exception e)
            {
                cout << "\nInvalid input. Try again." << endl;
            }
        }

        // STUDENT HAS ADVISOR; PROMPT FOR ID (MUST BE IN FACULTY TREE)
        if (answerInt == 1)
        {
            cout << "\nAdvisor ID: ";

            while (true)
            {
                answerInt = 0;
                answer = "";
                cin >> answer;

                // CHECK IF INPUT IS INTEGER; IF SO, FIND IN TREE IF POSSIBLE
                try
                {
                    a = stoi(answer);

                    // IF IN TREE, ADD STUDENT TO FACULTY MEMBER'S ADVISEE LIST & MAKE FACULTY MEMBER THE STUDENT'S ADVISOR
                    if (masterFaculty.isInTree(a))
                    {
                        Faculty *fac = masterFaculty.search(a);

                        fac->addAdvisee(i);

                        break;
                    }

                    else
                    {
                        cout << "\nFaculty member not found.";
                    }
                }

                catch (exception e)
                {
                    cout << "\nPlease enter an integer.";
                }
            }
        }

        else
        {
            a = -1;
        }
    }

    else
    {
        a = -1;
    }

    Student *stud = new Student(i, n, l, g, m, a);

    TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

    masterStudent.insert(studNode);
}

// PROMPTS FOR FACULTY INFO, CREATES FACULTY OBJECT, CREATES FACULTY NODE, INSERTS NODE INTO MASTER FACULTY
void Processor::addFaculty()
{
    cout << "\n--- ADDING NEW FACULTY MEMBER ---\n" << endl;

    int i;
    string n;
    string l;
    string d;

    int answerInt = 0;
    int numEntries = 0;
    string answer = "";

    while (true)
    {
        cout << "\nID of faculty member: ";

        answerInt = 0;
        answer = "";
        cin >> answer;

        try
        {
            i = stoi(answer);

            if (i > 0)
            {
                break;
            }
        }

        catch (exception e)
        {
            cout << "\nInvalid input. Try again." << endl;
        }
    }

    string line;

    cout << "\nName of faculty member: ";
    cin.ignore();
    getline(cin, n);

    cout << "\nLevel of faculty member: ";
    getline(cin, l);

    cout << "\nDepartment of faculty member: ";
    getline(cin, d);

    Faculty *fac = new Faculty(i, n, l, d);

    // IF IT IS POSSIBLE FOR THEM TO HAVE AN ADVISEE, PROMPT ACCORDINGLY
    if (!masterStudent.isEmpty())
    {
        cout << "\nDoes this facuty member have advisees?\n1 - Yes\n2 - No" << endl;

        while (true)
        {
            answerInt = 0;
            answer = "";
            cin >> answer;

            try
            {
                answerInt = stoi(answer);

                if (answerInt == 1 || answerInt == 2)
                {
                    break;
                }
            }

            catch (exception e)
            {
                cout << "\nInvalid input. Try again: ";
            }
        }

        // FACULTY MEMBER HAS ADVISEES; PROMPT FOR NUMBER (MUST BE <= SIZE OF STUDENT TREE)
        if (answerInt == 1 && !masterStudent.isEmpty())
        {
            cout << "\nHow many students does this faculty member advise?" << endl;

            while (true)
            {
                cout << "Please enter an integer: ";

                answerInt = 0;
                answer = "";
                cin >> answer;

                // CHECK IF INPUT IS A NUMBER
                try
                {
                    answerInt = stoi(answer);

                    if (answerInt > 0 && answerInt <= masterStudent.getSize())
                    {
                        numEntries = answerInt;
                        break;
                    }

                    else
                    {
                        cout << "\nPlease enter an integer less than or equal to " << masterStudent.getSize() << "." << endl;
                    }
                }

                catch (exception e)
                {
                    cout << "\nInvalid input. Please enter an integer.\n";
                }
            }

            for (int v = 0; v < numEntries; ++v)
            {
                while (true)
                {
                    cout << "Please enter a Student ID (" << numEntries - v << " remaining): ";

                    answerInt = 0;
                    answer = "";

                    //cout << "Please enter Student ID: ";
                    cin >> answer;

                    // CHECK IF INPUT IS INTEGER; IF SO, FIND IN TREE IF POSSIBLE
                    try
                    {
                        answerInt = stoi(answer);

                        // IF IN TREE, ADD STUDENT TO FACULTY MEMBER'S ADVISEE LIST & MAKE FACULTY MEMBER THE STUDENT'S ADVISOR
                        if (masterStudent.isInTree(answerInt))
                        {
                            fac->addAdvisee(answerInt);

                            //Student *stud = masterStudent.search(answerInt);

                            masterStudent.search(answerInt)->setAdvisorID(i);

                            break;
                        }

                        else
                        {
                            cout << "\nStudent not found.\n";
                        }
                    }

                    catch (exception e)
                    {
                        cout << "\nPlease enter an integer.\n";
                    }
                }
            }
        }
    }

    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, i);

    masterFaculty.insert(facNode);
}

// CREATES STUDENT OBJECT FROM PARAMETERS, CREATES STUDENT NODE, INSERTS NODE INTO MASTER STUDENT
void Processor::addStudentFromFile(int i, string n, string l, double g, string m, int a)
{
    Student *stud = new Student(i, n, l, g, m, a);

    TreeNode<Student> *studNode = new TreeNode<Student>(stud, i);

    masterStudent.insert(studNode);
}

// CREATES FACULTY OBJECT FROM PARAMETERS, CREATES FACULTY NODE, INSERTS NODE INTO MASTER FACULTY
void Processor::addFacultyFromFile(int i, string n, string l, string d)
{
    Faculty *fac = new Faculty(i, n, l, d);

    TreeNode<Faculty> *facNode = new TreeNode<Faculty>(fac, i);

    masterFaculty.insert(facNode);

    // come back to this when files are done
}

// PRINTS STUDENT INFO GIVEN STUDENT ID
void Processor::displayStudentInfo(int i)
{
    if (masterStudent.isInTree(i))
    {
        masterStudent.search(i)->printStudent();
    }

    else
    {
        cout << "\nStudent is not in system.\n\n<< Returning to Menu >>\n" << endl;
    }
}

// PRINTS FACULTY INFO GIVEN FACULTY ID
void Processor::displayFacultyInfo(int i)
{
    if (masterFaculty.isInTree(i))
    {
        masterFaculty.search(i)->printFaculty();
    }

    else
    {
        cout << "\nFaculty member is not in system.\n\n<< Returning to Menu >>\n" << endl;
    }
}

TreeNode<Student>* Processor::getMasterStudentRoot()
{
    return masterStudent.getRoot();
}

TreeNode<Faculty>* Processor::getMasterFacultyRoot()
{
    return masterFaculty.getRoot();
}

// RECEIVE INT INPUT BETWEEN PARAMETER BOUNDS AND DISPLAY MESSAGE ACCORDINGLY
int Processor::checkInput(int l, int u, string m)
{
    string answer;
    int answerInt;

    while (true)
    {
        cout << "\n" << m;

        answerInt = 0;
        answer = "";
        cin >> answer;

        // CHECK IF INPUT IS A NUMBER
        try
        {
            answerInt = stoi(answer);

            if (answerInt < u && answerInt > l)
            {

                return answerInt;
            }

            else
            {
                cout << "\nPlease try again." << endl;
            }
        }

        catch (exception e)
        {
            cout << "\nInvalid input. Please enter an integer.";
        }
    }
}

// RUNS CODE BASED ON MENU ITEM CHOSEN
void Processor::run()
{
    bool running = true;

    while (running)
    {
        int response;

        response = checkInput(-1, 15, "Please choose an option from the menu: ");

        switch (response)
        {
            // PRINT ALL STUDENTS AND THEIR INFO
            case 1:
            {
                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                cout << endl;
                printMasterStudent(masterStudent.getRoot());

                break;
            }

            // PRINT ALL FACULTY AND THEIR INFO
            case 2:
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<\n" << endl;

                    break;
                }

                cout << endl;
                printMasterFaculty(masterFaculty.getRoot());

                break;
            }

            // FIND AND DISPLAY STUDENT INFO
            case 3:
            {
                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                int t;

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        displayStudentInfo(t);

                        break;
                    }

                    else
                    {
                        cout << "\nStudent is not in database. Please enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            // FIND AND DISPLAY FACULTY INFO
            case 4:
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<\n" << endl;

                    break;
                }

                int t;

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        displayFacultyInfo(t);

                        break;
                    }
                }

                break;
            }

            // PRINT THE NAME AND INFO OF STUDENT ADVISOR
            case 5:
            {
                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                int t;

                cout << "\nCurrent students in database:\n" << endl;
                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        displayFacultyInfo(masterStudent.search(t)->getAdvisorID());

                        break;
                    }

                    else
                    {
                        cout << "\nStudent is not in database. Please enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            // PRINT INFO OF ALL ADVISEES OF FACULTY MEMBER
            case 6:
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<" << endl;

                    break;
                }

                int t;

                cout << "\nCurrent faculty members in database:\n" << endl;
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        Faculty *fac = masterFaculty.search(t);

                        for (int i = 0; i < fac->getMaxArraySize(); ++i)
                        {
                            if (fac->adviseeIDArray[i] != -1)
                            {
                                displayStudentInfo(fac->adviseeIDArray[i]);
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "\nFaculty member is not in database. Please enter a valid ID." << endl;
                    }
                }

                break;
            }

            // ADD A NEW STUDENT
            case 7:
            {
                addStudent();

                cout << "\n--- STUDENT ADDED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;

                break;
            }

            // DELETE A STUDENT
            case 8:
            {
                int t;

                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                cout << "Current students in database:\n";
                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Student ID: ");

                    if (masterStudent.isInTree(t))
                    {
                        if (masterStudent.search(t)->getAdvisorID() != -1)
                        {
                            masterFaculty.search(masterStudent.search(t)->getAdvisorID())->removeAdvisee(t);
                        }

                        masterStudent.deleteNode(t);

                        cout << "\n--- STUDENT DELETED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;

                        break;
                    }

                    else
                    {
                        cout << "\nStudent is not in database. Please enter a valid Student ID." << endl;
                    }
                }

                break;
            }

            // ADD A NEW FACULTY MEMBER
            case 9:
            {
                addFaculty();

                cout << "\n--- FACULTY MEMBER ADDED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;

                break;
            }

            // DELETE A FACULTY MEMBER
            case 10:
            {
                int t;

                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<\n" << endl;

                    break;
                }

                cout << "Current faculty members in database:\n";
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    t = checkInput(0, 10000, "Please enter a Faculty ID: ");

                    if (masterFaculty.isInTree(t))
                    {
                        if (masterFaculty.search(t)->numAdvisees > 0)
                        {
                            for (int i = 0; i < masterFaculty.search(t)->maxArraySize; ++i)
                            {
                                if (masterFaculty.search(t)->adviseeIDArray[i] != -1)
                                {
                                    masterStudent.search(masterFaculty.search(t)->adviseeIDArray[i])->setAdvisorID(-1);
                                }
                            }
                        }
                        masterFaculty.deleteNode(t);

                        cout << "\n--- FACULTY DELETED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;

                        break;
                    }

                    else
                    {
                        cout << "\nFaculty is not in database. Please enter a valid Faculty ID." << endl;
                    }
                }

                break;
            }

            // CHANGE A STUDENT’S ADVISOR
            case 11:
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<" << endl;

                    break;
                }

                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                int f;
                int s;

                cout << "Current students in database:\n";
                printMasterStudent(masterStudent.getRoot());

                while (true)
                {
                    s = checkInput(0, 10000, "Please enter a Student ID: ");

                    if (masterStudent.isInTree(s))
                    {
                        while (true)
                        {
                            f = checkInput(0, 10000, "Please enter a Faculty ID: ");

                            if (masterFaculty.isInTree(f))
                            {
                                break;
                            }

                            else
                            {
                                cout << "\nFaculty member is not in database. Please enter a valid ID." << endl;
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "\nStudent is not in database. Please enter a valid Student ID." << endl;
                    }
                }

                masterStudent.search(s)->setAdvisorID(f);

                masterFaculty.search(f)->addAdvisee(s);

                cout << "\n--- ADVISOR CHANGED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;

                break;
            }

            // REMOVE ADVISEE FROM FACULTY MEMBER
            case 12:
            {
                if (masterFaculty.isEmpty())
                {
                    cout << "\n>> No faculty members in database <<" << endl;

                    break;
                }

                if (masterStudent.isEmpty())
                {
                    cout << "\n>> No students in database <<\n" << endl;

                    break;
                }

                int f;
                int s;

                cout << "Current faculty members in database:\n";
                printMasterFaculty(masterFaculty.getRoot());

                while (true)
                {
                    f = checkInput(0, 10000, "Please enter a Faculty ID: ");

                    if (masterFaculty.isInTree(f))
                    {
                        cout << "\nThis Faculty Member currently avises: ";
                        masterFaculty.search(f)->printAdvisees();

                        while (true)
                        {
                            s = checkInput(0, 10000, "Please enter a Student ID: ");

                            if (masterStudent.isInTree(s))
                            {
                                break;
                            }

                            else
                            {
                                cout << "\nStudent is not in database. Please enter a valid Student ID." << endl;
                            }
                        }

                        break;
                    }

                    else
                    {
                        cout << "\nFaculty member is not in database. Please enter a valid ID." << endl;
                    }
                }

                if (masterFaculty.search(f)->removeAdvisee(s))
                {
                    masterStudent.search(s)->setAdvisorID(-1);

                    cout << "\n--- ADVISOR REMOVED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;
                }

                else
                {
                    cout << "\n--- ADVISOR *NOT* REMOVED ---\n\n>>> Returning to Menu <<<\n\n(Press '0' to display options)" << endl;
                }

                break;
            }

            // ROLLBACK
            case 13:
            {
                break;
            }

            // EXIT
            case 14:
            {
                running = false;

                cout << ">> Exiting Application <<" << endl;

                // WRITE TO FILES LATER
                break;
            }

            default:
            {
                Menu m;

                m.displayMenu();

                break;
            }
        }
    }
}

// // ATTEMPT TO SAVE COPY OF MASTER STUDETM FOR ROLLBACK FEATURE; DOES NOT WORK
// void Processor::saveTree(TreeNode<Student> *n)
// {
//     if (n != NULL)
//     {
//         masterStudent1.insert(n);
//
//         if (n->left != NULL)
//         {
//             saveTree(n->left);
//         }
//
//         if (n->right != NULL)
//         {
//             saveTree(n->right);
//         }
//     }
// }
