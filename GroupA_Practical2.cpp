/*
Experiment Number 2 : Develop a program in C++ to create a database of
student’s information system
containing the following information: Name, Roll number, Class, Division,
Date of Birth, Blood group,
Contactaddress, Telephone number, Driving license no. and other. Construct
the database with
suitable member functions. Make use of constructor, default constructor,
copy constructor,
destructor, static member functions, friend class, this pointer, inline
code and dynamic
memory allocation operators-new and delete as well as exception handling.
*/


#include<iostream>
#include<string.h>
using namespace std;

class StudData;

class Student {
    string name;         // Student's name
    int roll_no;         // Roll number of the student
    string cls;          // Class of the student
    char* division;      // Division of the student (dynamically allocated memory)
    string dob;          // Date of Birth of the student
    char* bloodgroup;    // Blood group of the student (dynamically allocated memory)
    static int count;    // Static variable to count the number of students

    public:

    // Default Constructor
    Student() {
        name = "";
        roll_no = 0;
        cls = "";
        division = new char;             // Dynamically allocate memory for division
        dob = "dd/mm/yyyy";              // Default date of birth
        bloodgroup = new char[4];        // Dynamically allocate memory for blood group
    }

    // Destructor
    ~Student() {
        delete division;                 // Release the memory allocated for division
        delete[] bloodgroup;             // Release the memory allocated for blood group
    }

    static int getCount() {
        return count;                    // Return the total number of students
    }

    void getData(StudData*);             // Function to get student data
    void dispData(StudData*);            // Function to display student data
};

class StudData {
    string caddress;        // Contact address of the student
    long int* telno;        // Telephone number (dynamically allocated memory)
    long int* dlno;         // Driving license number (dynamically allocated memory)
    friend class Student;   // Declaring Student as a friend class to access private members

    public:

    // Default Constructor
    StudData() {
        caddress = "";
        telno = new long;     // Dynamically allocate memory for telephone number
        dlno = new long;      // Dynamically allocate memory for driving license number
    }
    
    // Destructor
    ~StudData() {
        delete telno;         // Release the memory allocated for telephone number
        delete dlno;          // Release the memory allocated for driving license number
    }

    void getStudData() {
        cout << "Enter Contact Address: ";
        cin.get();            //  input buffer
        getline(cin, caddress);
        cout << "Enter Telephone Number: ";
        cin >> *telno;
        cout << "Enter Driving License Number: ";
        cin >> *dlno;
    }

    void dispStudData() {
        cout << "Contact Address: " << caddress << endl;
        cout << "Telephone Number: " << *telno << endl;
        cout << "Driving License Number: " << *dlno << endl;
    }
};

// Function to get student data
inline void Student::getData(StudData* st) {
    cout << "Enter Student Name: ";
    getline(cin, name);
    cout << "Enter Roll Number: ";
    cin >> roll_no;
    cout << "Enter Class: ";
    cin.get();                // input buffer
    getline(cin, cls);
    cout << "Enter Division: ";
    cin >> division;
    cout << "Enter Date of Birth: ";
    cin.get();                // input buffer
    getline(cin, dob);
    cout << "Enter Blood Group: ";
    cin >> bloodgroup;
    st->getStudData();        // Get additional data from StudData class
    count++;                  // Increment the student count
}

// Function to display student data
inline void Student::dispData(StudData* st1) {
    cout << "Student Name: " << name << endl;
    cout << "Roll Number: " << roll_no << endl;
    cout << "Class: " << cls << endl;
    cout << "Division: " << division << endl;
    cout << "Date of Birth: " << dob << endl;
    cout << "Blood Group: " << bloodgroup << endl;
    st1->dispStudData();      // Display additional data from StudData class
}

int Student::count;           // Initialize static variable count to 0

int main() {
    Student* stud1[100];      // Array of pointers to Student objects
    StudData* stud2[100];     // Array of pointers to StudData objects
    int n = 0;                // Number of students
    char ch;

    do {
        stud1[n] = new Student;     // Create a new Student object
        stud2[n] = new StudData;    // Create a new StudData object
        stud1[n]->getData(stud2[n]);// Get data for the new student
        n++;
        cout << "Do you want to add another student (y/n): ";
        cin >> ch;
        cin.get();                  // input buffer
    } while (ch == 'y' || ch == 'Y');

    for (int i = 0; i < n; i++) {
        cout << "---------------------------------------------------------------" << endl;
        stud1[i]->dispData(stud2[i]); // Display the data of each student
    }

    cout << "---------------------------------------------------------------" << endl;
    cout << "Total Students: " << Student::getCount(); // Display the total number of students
    cout << endl << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        delete stud1[i];       // Release memory allocated for each Student object
        delete stud2[i];       // Release memory allocated for each StudData object
    }

    return 0;
}
