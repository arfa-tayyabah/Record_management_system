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
class FileHandler {
public:
    void saveStudent(Student s) {
        ofstream fout("students.txt", ios::app);
        fout << s.roll << " " << s.name << " " << s.department << " "
             << s.gpa << " " << s.contact << endl;
        fout.close();
    }

    void displayAll() {
        ifstream fin("students.txt");
        Student s;
        cout << "\nAll Student Records:\n";
        while (fin >> s.roll >> s.name >> s.department >> s.gpa >> s.contact) {
            cout << "Roll: " << s.roll << ", Name: " << s.name
                 << ", Dept: " << s.department << ", GPA: " << s.gpa
                 << ", Contact: " << s.contact << endl;
        }
        fin.close();
    }

    bool isRollExist(int roll) {
        ifstream fin("students.txt");
        Student s;
        while (fin >> s.roll >> s.name >> s.department >> s.gpa >> s.contact) {
            if (s.roll == roll) { fin.close(); return true; }
        }
        fin.close();
        return false;
    }

    void updateStudent(int roll, Student updated) {
        ifstream fin("students.txt");
        ofstream temp("temp.txt");
        Student s;
        bool found = false;
        while (fin >> s.roll >> s.name >> s.department >> s.gpa >> s.contact) {
            if (s.roll == roll) {
                temp << updated.roll << " " << updated.name << " "
                     << updated.department << " " << updated.gpa << " "
                     << updated.contact << endl;
                found = true;
            } else {
                temp << s.roll << " " << s.name << " " << s.department << " "
                     << s.gpa << " " << s.contact << endl;
            }
        }
        fin.close(); temp.close();
        remove("students.txt"); rename("temp.txt","students.txt");
        if (found) cout << "Record updated.\n"; else cout << "Roll not found.\n";
    }

    void deleteStudent(int roll) {
        ifstream fin("students.txt");
        ofstream temp("temp.txt");
        Student s; bool found=false;
        while (fin >> s.roll >> s.name >> s.department >> s.gpa >> s.contact) {
            if (s.roll == roll) { found = true; continue; }
            temp << s.roll << " " << s.name << " " << s.department << " "
                 << s.gpa << " " << s.contact << endl;
        }
        fin.close(); temp.close();
        remove("students.txt"); rename("temp.txt","students.txt");
        if (found) cout << "Record deleted.\n"; else cout << "Roll not found.\n";
    }

    void viewByRoll(int roll) {
        ifstream fin("students.txt");
        Student s; bool found=false;
        while (fin >> s.roll >> s.name >> s.department >> s.gpa >> s.contact) {
            if (s.roll == roll) {
                cout << "Roll: " << s.roll << ", Name: " << s.name
                     << ", Dept: " << s.department << ", GPA: " << s.gpa
                     << ", Contact: " << s.contact << endl;
                found=true; break;
            }
        }
        fin.close();
        if (!found) cout << "Student not found.\n";
    }
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

