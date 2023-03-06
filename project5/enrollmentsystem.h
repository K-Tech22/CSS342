#ifndef ENROLLMENTSYSTEM_H
#define ENROLLMENTSYSTEM_H

#include "university.h"
#include <map>
#include <string>

using namespace std;

class EnrollmentSystem
{

public:
    // Add university to the enrollments system
    bool addUniversity(const string &name);

    // Set this university as the active university for other functions
    bool setCurrentUniversity(const string &name);

    // Return the current active university name
    string getUniversityName() const;

    // Read the student list for current active university
    // return true if file successfully read
    bool readStudentList(const string &filename);

    // Read the course list for current active university
    // return true if file successfully read
    bool readCourseList(const string &filename);

    // Read the student enrollment information for current active university
    // return true if file successfully read
    bool readEnrollmentInfo(const string &filename);

    // Drop student from given course, return true if successful
    bool dropCourse(int studentID, const string &courseNumber);

    // Add student to the given course, return true if successful
    bool addCourse(int studentID, const string &courseNumber);

    // Return true if student is in the given course
    bool isInCourse(int studentID, const string &courseNumber) const;

    // Return the courses student is enrolled in
    // The returned courses are separated by commas and sorted by course name
    string getEnrolledCourses(int studentID) const;

    // Return the title for the course
    string getCourseTitle(const string &courseNumber);

    // Return class list sorted by last name of students
    string getClassListByLastName(const string &courseNumber) const;

    // Return class list sorted by id of students
    string getClassListByID(const string &courseNumber) const;

private:
    // current active university
    University *currentUniversity;

    // Store of known universities
    map<string, University *> universities;
};
#endif
