#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ------------------ Member 1 ------------------
class Student {
public:
    int roll;
    string name;
    string department;
    float gpa;
    string contact;
};

// ------------------ Member 3 ------------------
class StudentManager {
public:
    FileHandler file;
    void addStudent() {
        Student s;
        cout << "Enter Roll: "; cin >> s.roll;
        if (file.isRollExist(s.roll)) { cout << "Roll already exists.\n"; return; }
        cout << "Enter Name: "; cin >> s.name;
        cout << "Enter Department: "; cin >> s.department;
        cout << "Enter GPA: "; cin >> s.gpa;
        cout << "Enter Contact: "; cin >> s.contact;
        file.saveStudent(s);
        cout << "Student Added.\n";
    }
    void updateStudent() {
        int roll; cout << "Enter Roll to Update: "; cin >> roll;
        if (!file.isRollExist(roll)) { cout << "Roll not found.\n"; return; }
        Student s; s.roll=roll;
        cout << "Enter New Name: "; cin >> s.name;
        cout << "Enter New Department: "; cin >> s.department;
        cout << "Enter New GPA: "; cin >> s.gpa;
        cout << "Enter New Contact: "; cin >> s.contact;
        file.updateStudent(roll,s);
    }
    void deleteStudent() {
        int roll; cout << "Enter Roll to Delete: "; cin >> roll;
        file.deleteStudent(roll);
    }
    void viewAll() { file.displayAll(); }
    void viewByRoll() { int roll; cout << "Enter Roll: "; cin >> roll; file.viewByRoll(roll); }
};
int main() {
    Interface i;
    i.menu();
    return 0;
}

