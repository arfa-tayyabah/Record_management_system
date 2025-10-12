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
int main() {
    Interface i;
    i.menu();
    return 0;
}
