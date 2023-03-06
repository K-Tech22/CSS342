/*
 *
 * course.h
 * Header file for the Course object
 * Developed by: Matthew Ovanesyan, Siraj Dabbagh, Kush Chopra, Imran Popal
 * December 4, 2022
 *
 */
#ifndef COURSE_H
#define COURSE_H

#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// forward declaration
class Student;

class Course
{
    friend class Student;
    friend class University;
    friend class EnrollmentSystem;

public:
    // Constructor
    Course(const string &courseID, const string &courseName);

    // Destructor
    // ~Course();

private:
    // Name of course
    string nameofCourse;

    // Course ID as in CSS342
    string cID;

    // Container for student objects in a course
    // Keys are studentIDs, and values are pointers to Student objects with that
    // ID This container acts as a list of students belonging to (enrolled) in a
    // course
    map<int, Student *> studentList;
};

#endif