#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

// Structure to store student information
struct Student {
    string name;
    string department;
    double gpa;
    string contact;
};

// Function prototypes for file handling
void saveToFile(const string& filename, const map<string, Student>& students);
void loadFromFile(const string& filename, map<string, Student>& students);

void saveToFile(const string& filename, const map<string, Student>& students) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open " << filename << " for writing.\n";
        return;
    }

    for (const auto& pair : students) {
        const string& roll = pair.first;
        const Student& student = pair.second;
        string line = roll + "," + student.name + "," + student.department + "," +
                      to_string(student.gpa) + "," + student.contact;
        file << line << endl;
    }

    file.close();
    cout << "Data saved to " << filename << " successfully.\n";
}

void loadFromFile(const string& filename, map<string, Student>& students) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Warning: " << filename << " not found. Starting with empty records.\n";
        return;
    }

    students.clear(); // Clear existing records to avoid duplicates
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string roll, name, dept, contact;
        double gpa;
        char delimiter;

        // Parse the line: roll,name,department,gpa,contact
        if (getline(ss, roll, ',') &&
            getline(ss, name, ',') &&
            getline(ss, dept, ',') &&
            (ss >> gpa >> delimiter) &&
            getline(ss, contact)) {
            Student student = {name, dept, gpa, contact};
            students[roll] = student;
        } else {
            cout << "Error: Invalid file format in " << filename << " at line: " << line << endl;
        }
    }

    file.close();
    cout << "Data loaded from " << filename << " successfully.\n";
}
