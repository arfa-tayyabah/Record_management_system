#include <iostream>
#include <fstream>
#include <string>
using namespace std;
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
class Interface {
public:
    void menu() {
        StudentManager sm;
        SearchAndSort ss;
        int ch;
        while (true) {
            cout << "\n==== Student Record System ====\n";
            cout << "1. Add Student\n";
            cout << "2. View All Students\n";
            cout << "3. View Student by Roll\n";
            cout << "4. Update Student\n";
            cout << "5. Delete Student\n";
            cout << "6. Search by Name\n";
            cout << "7. Search by Department\n";
            cout << "8. Sort by Roll\n";
            cout << "9. Sort by GPA\n";
            cout << "10. Exit\n";
            cout << "Enter choice: ";
            cin >> ch;
            if (ch==1) sm.addStudent();
            else if (ch==2) sm.viewAll();
            else if (ch==3) sm.viewByRoll();
            else if (ch==4) sm.updateStudent();
            else if (ch==5) sm.deleteStudent();
            else if (ch==6) { string n; cout<<"Enter Name: "; cin>>n; ss.searchByName(n); }
            else if (ch==7) { string d; cout<<"Enter Department: "; cin>>d; ss.searchByDepartment(d); }
            else if (ch==8) ss.sortByRoll();
            else if (ch==9) ss.sortByGPA();
            else if (ch==10) break;
            else cout << "Invalid choice.\n";
        }
    }
};
int main() {
    Interface i;
    i.menu();
    return 0;
}

