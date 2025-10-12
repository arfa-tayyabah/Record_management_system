#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>
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
void addStudent(map<string, Student>& students) {
    string roll;
    cout << "\nEnter Roll Number: ";
    cin >> roll;

    if (students.find(roll) != students.end()) {
        cout << "❌ Record with Roll Number " << roll << " already exists.\n";
        return;
    }

    Student s;
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);

    cout << "Enter Department: ";
    getline(cin, s.department);

    cout << "Enter GPA (0.0 - 4.0): ";
    cin >> s.gpa;
    while (cin.fail() || s.gpa < 0.0 || s.gpa > 4.0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid GPA. Enter again (0.0 - 4.0): ";
        cin >> s.gpa;
    }

    cout << "Enter Contact Number: ";
    cin.ignore();
    getline(cin, s.contact);

    students[roll] = s;
    cout << "✅ Student record added successfully.\n";
}

// Update student
void updateStudent(map<string, Student>& students) {
    string roll;
    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    auto it = students.find(roll);
    if (it == students.end()) {
        cout << "❌ No record found for Roll Number " << roll << ".\n";
        return;
    }

    Student& s = it->second;
    cout << "Updating record for " << s.name << " (" << roll << ")\n";

    cout << "Enter new name (or press Enter to keep '" << s.name << "'): ";
    cin.ignore();
    string name;
    getline(cin, name);
    if (!name.empty()) s.name = name;

    cout << "Enter new department (or press Enter to keep '" << s.department << "'): ";
    string dept;
    getline(cin, dept);
    if (!dept.empty()) s.department = dept;

    cout << "Enter new GPA (or -1 to keep current " << s.gpa << "): ";
    double gpa;
    cin >> gpa;
    if (!cin.fail() && gpa >= 0.0 && gpa <= 4.0)
        s.gpa = gpa;
    else if (gpa != -1)
        cout << "⚠️ Invalid GPA, keeping old value.\n";

    cout << "Enter new contact (or press Enter to keep '" << s.contact << "'): ";
    cin.ignore();
    string contact;
    getline(cin, contact);
    if (!contact.empty()) s.contact = contact;

    cout << "✅ Student record updated successfully.\n";
}

// Delete student
void deleteStudent(map<string, Student>& students) {
    string roll;
    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    if (students.erase(roll))
        cout << "✅ Record deleted successfully.\n";
    else
        cout << "❌ No record found for Roll Number " << roll << ".\n";
}

// Display all students
void displayStudents(const map<string, Student>& students) {
    if (students.empty()) {
        cout << "⚠️ No student records available.\n";
        return;
    }

    cout << "\n----- Student Records -----\n";
    for (const auto& pair : students) {
        cout << "Roll: " << pair.first
             << " | Name: " << pair.second.name
             << " | Dept: " << pair.second.department
             << " | GPA: " << pair.second.gpa
             << " | Contact: " << pair.second.contact << endl;
    }
    cout << "-----------------------------\n";
}

int main() {
    map<string, Student> students;
    string filename = "students.txt";

    loadFromFile(filename, students);

    int choice;
    do {
        cout << "\n===== Student Management Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Display All Students\n";
        cout << "5. Save and Exit\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: updateStudent(students); break;
            case 3: deleteStudent(students); break;
            case 4: displayStudents(students); break;
            case 5: saveToFile(filename, students); break;
            default: cout << "❌ Invalid choice. Try again.\n"; break;
        }
    } while (choice != 5);

    return 0;
}

