#include "student.h"
#include "course.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Constructor
Student::Student(const int &studentID, const string &name)
{
    idOfStudent = studentID;
    nameOfStudent = name;
}

// Returns the student's last name
string Student::getLastName(string const &name)
{
    vector<string> ans;
    istringstream ss(name);
    string del;
    // Iterates through the name & separates the last name
    while (getline(ss, del, ' '))
    {
        ans.push_back(del);
    }
    return ans[1];
}

// Returns the student's last name
string Student::getFirstName(string const &name)
{
    vector<string> ans;
    istringstream ss(name);
    string del;
    // Iterates through the name & separates the last name
    while (getline(ss, del, ' '))
    {
        ans.push_back(del);
    }
    return ans[0];
}
