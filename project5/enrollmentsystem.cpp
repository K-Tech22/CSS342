#include "enrollmentsystem.h"
#include "university.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Returns true if university added succesfully
bool EnrollmentSystem::addUniversity(const string &name)
{
    // If university does not exist, adds the university in the container
    if (universities.count(name) == 0)
    {
        universities[name] = new University(name);
        return true;
    }
    return false;
}

// Returns true if university successfully set as current university
bool EnrollmentSystem::setCurrentUniversity(const string &name)
{
    // Checks if university exists in the university container
    if (universities.count(name) == 1)
    {
        currentUniversity = universities[name];
        return true;
    }
    return false;
}

// Returns current university's name
string EnrollmentSystem::getUniversityName() const
{
    return currentUniversity->nameOfUniversity;
}

// Returns true if file read successfully
bool EnrollmentSystem::readCourseList(const string &filename)
{
    // Calls university class
    return currentUniversity->readCourseList(filename);
}

// Returns true if file read successfully
bool EnrollmentSystem::readStudentList(const string &filename)
{
    // Calls university class
    return currentUniversity->readStudentList(filename);
}

// Returns true if file read successfully
bool EnrollmentSystem::readEnrollmentInfo(const string &filename)
{
    // Calls university class
    return currentUniversity->readEnrollmentInfo(filename);
}

// Returns true if added course successfully
bool EnrollmentSystem::addCourse(int studentID, const string &courseNumber)
{
    // Calls university class
    return currentUniversity->addCourse(studentID, courseNumber);
}

// Returns true if student is enrolled in course
bool EnrollmentSystem::isInCourse(int studentID,
                                  const string &courseNumber) const
{
    // Calls university class
    return currentUniversity->isInCourse(studentID, courseNumber);
}

// Returns true if student successfully dropped from course
bool EnrollmentSystem::dropCourse(int studentID, const string &courseNumber)
{
    // Calls university class
    return currentUniversity->dropCourse(studentID, courseNumber);
}

// Returns the course title
string EnrollmentSystem::getCourseTitle(const string &courseNumber)
{
    // Calls university class
    return currentUniversity->getCourseTitle(courseNumber);
}

// Returns a list of students enrolled in a course
string EnrollmentSystem::getClassListByID(const string &courseNumber) const
{
    // Calls university class
    return currentUniversity->getClassListByID(courseNumber);
}

// Returns the courses a student is enrolled in
string EnrollmentSystem::getEnrolledCourses(int studentID) const
{
    // Calls university class
    return currentUniversity->getEnrolledCourses(studentID);
}

// Returns a list of students enrolled in a course
string
EnrollmentSystem::getClassListByLastName(const string &courseNumber) const
{
    // Calls university class
    return currentUniversity->getClassListByLastName(courseNumber);
}
