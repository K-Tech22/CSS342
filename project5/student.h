#ifndef STUDENT_H
#define STUDENT_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Course;

class Student
{
    friend class Course;
    friend class University;
    friend class EnrollmentSystem;

public:
    // Constructor
    Student(const int &studentID, const string &name);

    // Destructor
    // ~Student();

private:
    // Name of the student
    string nameOfStudent;

    // Student ID
    int idOfStudent;

    // Container for courses for each student
    // Keys are course names, and values are pointers to Course objects with that
    // name This container acts as a list of courses a student belongs to
    map<string, Course *> StudentCourses;

    // Returns the student's last name
    string getLastName(string const &name);

    // Returns the student's first name
    string getFirstName(string const &name);
};

#endif
