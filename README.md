# Student Record Management System

A console-based C++ application designed to manage student records efficiently, built as a collaborative project to demonstrate programming skills and effective use of Git and GitHub for version control.

## Project Description

The **Student Record Management System** allows teachers or administrators to manage student data through a simple command-line interface. The system supports adding, viewing, updating, deleting, searching, and sorting student records, with data persistence using file handling. This project showcases teamwork, modular C++ programming, and Git-based collaboration.

### Features

1. **Add New Student Record**:
   - Input: Name, Roll Number, Department, GPA, Contact Info.
   - Validates unique roll numbers to prevent duplicates.

2. **View Student Records**:
   - Displays all records in a tabular format.
   - Allows viewing a specific student's details by roll number.

3. **Update Student Information**:
   - Edit existing student data (e.g., GPA, contact info) by roll number.

4. **Delete Student Record**:
   - Remove a student record using their roll number.

5. **File Handling**:
   - Stores records in `students.txt` for persistence across program runs.

6. **Search & Sorting**:
   - Search students by name or department.
   - Sort records by GPA or roll number.

## Technologies Used

- **Language**: C++ (Standard Library, including `map`, `fstream`, `string`, `iomanip`)
- **Tools**: Git, GitHub
- **File Storage**: Text file (`students.txt`) for persistent data storage
- **Development Environment**: Any C++ compiler (e.g., g++, MinGW)

## Prerequisites

- C++ compiler (e.g., `g++` on Linux/Mac, MinGW on Windows)
- Git installed (`git --version` to check)
- GitHub account for collaboration
- Terminal or command-line interface
- Optional: Text editor (e.g., `nano`, `vim`, VS Code)

