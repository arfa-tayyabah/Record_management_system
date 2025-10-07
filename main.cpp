#include <iostream>
#include <map>
#include <string>
using namespace std;

// Structure to store student information
struct Student {
    string name;
    string department;
    double gpa;
    string contact;
};

// Function prototypes
void addStudent(map<string, Student>& students);
void updateStudent(map<string, Student>& students);
void deleteStudent(map<string, Student>& students);
void displayMenu();

int main() {
    map<string, Student> students; // Map to store student records with roll number as key
    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice (1-4): ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                updateStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

void displayMenu() {
    cout << "\n=== Student Record Management System ===\n";
    cout << "1. Add New Student\n";
    cout << "2. Update Student Information\n";
    cout << "3. Delete Student Record\n";
    cout << "4. Exit\n";
}

void addStudent(map<string, Student>& students) {
    string roll, name, dept, contact;
    double gpa;

    cout << "\nEnter Roll Number: ";
    getline(cin, roll);

    // Check if roll number already exists
    if (students.find(roll) != students.end()) {
        cout << "Error: Roll number already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Department: ";
    getline(cin, dept);
    cout << "Enter GPA: ";
    cin >> gpa;
    cin.ignore(); // Clear newline
    cout << "Enter Contact Info: ";
    getline(cin, contact);

    // Create student record
    Student student = {name, dept, gpa, contact};
    students[roll] = student;
    cout << "Student record added successfully.\n";
}

void updateStudent(map<string, Student>& students) {
    string roll;
    cout << "\nEnter Roll Number to update: ";
    getline(cin, roll);

    // Check if student exists
    if (students.find(roll) == students.end()) {
        cout << "Error: Student not found.\n";
        return;
    }

    Student& student = students[roll];
    string input;

    cout << "Enter new values (press Enter to keep current value):\n";
    cout << "Name (" << student.name << "): ";
    getline(cin, input);
    if (!input.empty()) student.name = input;

    cout << "Department (" << student.department << "): ";
    getline(cin, input);
    if (!input.empty()) student.department = input;

    cout << "GPA (" << student.gpa << "): ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            student.gpa = stod(input);
        } catch (...) {
            cout << "Invalid GPA. Keeping current value.\n";
        }
    }

    cout << "Contact Info (" << student.contact << "): ";
    getline(cin, input);
    if (!input.empty()) student.contact = input;

    cout << "Student record updated successfully.\n";
}

void deleteStudent(map<string, Student>& students) {
    string roll;
    cout << "\nEnter Roll Number to delete: ";
    getline(cin, roll);

    // Check if student exists
    if (students.find(roll) == students.end()) {
        cout << "Error: Student not found.\n";
        return;
    }

    students.erase(roll);
    cout << "Student record deleted successfully.\n";
}
