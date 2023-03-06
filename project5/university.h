#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "course.h"
#include "student.h"
#include <map>
#include <string>

#include <vector>

using namespace std;

class University
{
    friend class EnrollmentSystem;

public:
    // Constructor
    University(const string &name);

    // Destructor
    // ~University();

private:
    // Name of the university
    string nameOfUniversity;

    // Course pointers
    // Key is a courseID & value is a Course pointer
    // Acts as a list of Courses belonging to the University
    map<string, Course *> coursePointers;

    // Student pointers
    // Key is a studentID & value is a Student pointer
    // Acts as a list of Students belonging to the University
    map<int, Student *> studentPointers;

    // Reads the list of Student ID : name pairs from the txt file
    // Creates new Student objects with ID and name from the txt file
    // Populates studentPointers with Student pointer which point to the new
    // Student objects
    bool readStudentList(const string &fileName);

    // Reads the list of Course ID : description pairs from the txt file
    // Creates new Student objects with ID and name from the txt file
    // Populates studentPointers with Student pointer which point to the new
    // Student objects
    bool readCourseList(const string &fileName);

    // Reads the list of enrollments from the txt file
    // Creates new Course objects with studentID and courseID from the txt file
    // Populates studentPointers with Student pointer which point to the new
    // Student objects
    bool readEnrollmentInfo(const string &fileName);

    // Drop Student from given Course, return true if successful
    bool dropCourse(int studentID, const string &courseNumber);

    // Add Student to the given Course, return true if successful
    bool addCourse(int studentID, const string &courseNumber);

    // Return true if Student is in the given Course
    bool isInCourse(int studentID, const string &courseNumber) const;

    // Return the Courses the Student is enrolled in
    // The returned Courses are separated by commas and sorted by Course name
    string getEnrolledCourses(int studentID) const;

    // Return the title for the course
    string getCourseTitle(const string &courseNumber);

    // Return class list sorted by last name of Students
    string getClassListByLastName(const string &courseNumber) const;

    // Return class list sorted by id of Students
    string getClassListByID(const string &courseNumber) const;
};

#endif
