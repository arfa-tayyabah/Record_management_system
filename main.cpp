
#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "Student.h" // Assumes Student.h has the Student struct

using namespace std;

// Show all students in a table
void displayAllStudents(const map<string, Student>& students) {
    if (students.empty()) {
        cout << "\nNo students found.\n" << endl;
        return;
    }

    cout << "\nAll Students:\n";
    cout << left << setw(15) << "Roll No." << setw(20) << "Name" << setw(15) << "Department" 
         << setw(8) << "GPA" << setw(20) << "Contact" << endl;
    cout << string(78, '-') << endl;

    for (const auto& pair : students) {
        cout << left << setw(15) << pair.first << setw(20) << pair.second.name 
             << setw(15) << pair.second.department << setw(8) << fixed << setprecision(2) 
             << pair.second.gpa << setw(20) << pair.second.contact << endl;
    }
    cout << string(78, '-') << endl;
}

// Show details of one student by roll number
void displayStudentByRoll(const map<string, Student>& students, const string& roll) {
    auto it = students.find(roll);
    if (it == students.end()) {
        cout << "\nStudent with Roll Number " << roll << " not found.\n" << endl;
        return;
    }

    const Student& student = it->second;
    cout << "\nStudent Details:\n";
    cout << "Roll Number: " << roll << endl;
    cout << "Name: " << student.name << endl;
    cout << "Department: " << student.department << endl;
    cout << "GPA: " << fixed << setprecision(2) << student.gpa << endl;
    cout << "Contact: " << student.contact << endl;
}

// Search students by name (not case-sensitive)
void searchByName(const map<string, Student>& students, const string& searchName) {
    map<string, Student> results;
    string lowerSearch = searchName;
    for (char& c : lowerSearch) c = tolower(c);

    for (const auto& pair : students) {
        string lowerName = pair.second.name;
        for (char& c : lowerName) c = tolower(c);
        if (lowerName.find(lowerSearch) != string::npos) {
            results[pair.first] = pair.second;
        }
    }

    if (results.empty()) {
        cout << "\nNo students found with name \"" << searchName << "\".\n" << endl;
    } else {
        cout << "\nStudents with Name \"" << searchName << "\":\n";
        displayAllStudents(results);
    }
}

// Search students by department (not case-sensitive)
void searchByDepartment(const map<string, Student>& students, const string& searchDept) {
    map<string, Student> results;
    string lowerSearch = searchDept;
    for (char& c : lowerSearch) c = tolower(c);

    for (const auto& pair : students) {
        string lowerDept = pair.second.department;
        for (char& c : lowerDept) c = tolower(c);
        if (lowerDept.find(lowerSearch) != string::npos) {
            results[pair.first] = pair.second;
        }
    }

    if (results.empty()) {
        cout << "\nNo students found in department \"" << searchDept << "\".\n" << endl;
    } else {
        cout << "\nStudents in Department \"" << searchDept << "\":\n";
        displayAllStudents(results);
    }
}

// Sort students by GPA (highest to lowest)
void sortByGPA(const map<string, Student>& students) {
    if (students.empty()) {
        cout << "\nNo students to sort.\n" << endl;
        return;
    }

    vector<pair<string, Student>> studentList(students.begin(), students.end());
    sort(studentList.begin(), studentList.end(), [](const auto& a, const auto& b) {
        return a.second.gpa > b.second.gpa;
    });

    map<string, Student> sortedStudents(studentList.begin(), studentList.end());
    cout << "\nStudents Sorted by GPA (High to Low):\n";
    displayAllStudents(sortedStudents);
}

// Sort students by roll number (A to Z)
void sortByRollNumber(const map<string, Student>& students) {
    if (students.empty()) {
        cout << "\nNo students to sort.\n" << endl;
        return;
    }

    vector<pair<string, Student>> studentList(students.begin(), students.end());
    sort(studentList.begin(), studentList.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    map<string, Student> sortedStudents(studentList.begin(), studentList.end());
    cout << "\nStudents Sorted by Roll Number (A to Z):\n";
    displayAllStudents(sortedStudents);
}