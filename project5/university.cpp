#include "university.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Constructor
University::University(const string &name) { nameOfUniversity = name; }

// Reads the courseInfo file and assins elements in coursePointers container
bool University::readCourseList(const string &fileName)
{
    string test, code, rest;
    ifstream ReadCourseList(fileName);
    while (ReadCourseList >> code)
    {
        ReadCourseList.get();
        getline(ReadCourseList, rest);
        // If course already exists, skip
        if (coursePointers.count(code) > 0)
        {
            continue;
        }
        else
        {
            // Else, adds the course to the container
            coursePointers[code] = new Course(code, rest);
        }
    }
    return true;
}

// Reads the studentInfo file and assins elements in studentPointers container
bool University::readStudentList(const string &fileName)
{
    string test, fullName;
    int id;
    ifstream ReadStudentList(fileName);
    while (ReadStudentList >> id)
    {
        ReadStudentList.get();
        getline(ReadStudentList, fullName);
        // If studentID already exists, skip
        if (studentPointers.count(id) > 0)
        {
            continue;
        }
        // Adds the student to the container
        studentPointers[id] = new Student(id, fullName);
    }
    return true;
}

// Reads the enrollmentInfo and adds students to their courses
bool University::readEnrollmentInfo(const string &fileName)
{
    int id;
    string code, test;
    ifstream ReadEnrollmentInfo(fileName);
    while (ReadEnrollmentInfo >> id)
    {
        ReadEnrollmentInfo.get();
        getline(ReadEnrollmentInfo, code);
        // If studentID or courseID is invalid, skip
        if (studentPointers.count(id) == 0 || coursePointers.count(code) == 0)
        {
            continue;
        }
        // Gets the student from the studentID
        Student *s = studentPointers[id];
        // Gets the course from the courseID
        Course *c = coursePointers[code];
        // Adds course to student's courses container
        s->StudentCourses[code] = c;
        // Adds student to course container
        c->studentList[id] = s;
    }
    return true;
}

// Adds student into the course and returns true if sucessfully added
bool University::addCourse(int studentID, const string &courseNumber)
{
    // If courseNumber or studentID is invalid, returns false
    if (coursePointers.count(courseNumber) == 0 ||
        studentPointers.count(studentID) == 0)
    {
        return false;
    }
    // If studentID exists
    if (studentPointers.count(studentID) == 1)
    {
        // Gets the student from studentID
        Student *s = studentPointers[studentID];
        // Gets the course from courseID
        Course *c = coursePointers[courseNumber];
        // Assigns the course to student
        s->StudentCourses[courseNumber] = c;
        // Assigns the student to course
        c->studentList[studentID] = s;
        return true;
    }
    return false;
}

// Returns true if student is in course, otherwise returns false
bool University::isInCourse(int studentID, const string &courseNumber) const
{
    // Returns false if studentID or courseNumber is invalid
    if (coursePointers.count(courseNumber) == 0 ||
        studentPointers.count(studentID) == 0)
    {
        return false;
    }
    if (studentPointers.count(studentID) == 1)
    {
        // Gets the student from the students container
        Student *s = studentPointers.at(studentID);
        // Checks if student is in course
        if (s->StudentCourses[courseNumber])
        {
            return true;
        }
    }
    return false;
}

// Returns the courseTitle from courseNumber
string University::getCourseTitle(const string &courseNumber)
{
    // Gets the course object from course container
    Course *c = coursePointers[courseNumber];
    return c->nameofCourse;
}

// Returns true if student dropped from the course successfully
bool University::dropCourse(int studentID, const string &courseNumber)
{
    // Returns false if studentID or courseNumber is invalid
    if (studentPointers.count(studentID) == 0 ||
        coursePointers.count(courseNumber) == 0)
    {
        return false;
    }
    // Gets the student object from student container
    Student *s = studentPointers[studentID];
    // Erases the course from the student's courses container
    s->StudentCourses.erase(courseNumber);
    // Gets the course object from course container
    Course *c = coursePointers[courseNumber];
    // Erases the student from the course's student container
    c->studentList.erase(studentID);
    return true;
}

// Returns a sorted string of courses that the student is enrolled in
string University::getEnrolledCourses(int studentID) const
{
    // If studentID is inavlid, returns "[]"
    if (studentPointers.at(studentID) == 0)
    {
        return "[]";
    }
    vector<string> res;
    string ans;
    // Gets the student object from student container
    Student *s = studentPointers.at(studentID);
    auto it = s->StudentCourses.begin();
    // Iterates through the student's courses container
    while (it != s->StudentCourses.end())
    {
        // Adds each course to the vector
        res.push_back((*it).first);
        ++it;
    }
    // Sorts the vector
    sort(res.begin(), res.end());
    ans += "[";
    // Loops through the vector and adds each course to the string
    for (int i = 0; i < res.size(); ++i)
    {
        if (i == 0)
        {
            ans += res[i];
        }
        else
        {
            ans += ", " + res[i];
        }
    }
    ans += "]";
    return ans;
}

// Returns a sorted list of students enrolled in the course as a string
string University::getClassListByLastName(const string &courseNumber) const
{
    // Returns "[]" if courseNumber is invalid
    if (coursePointers.at(courseNumber) == 0)
    {
        return "[]";
    }
    vector<string> ans;
    string res;
    // Gets the course object from course container
    Course *c = coursePointers.at(courseNumber);
    auto it = c->studentList.begin();
    // Iterates through the course's student container
    while (it != c->studentList.end())
    {
        Student *s = c->studentList[(*it).first];
        string name;
        name = s->getLastName(s->nameOfStudent) + ", " +
               s->getFirstName(s->nameOfStudent) + " (" +
               to_string(s->idOfStudent) + ")";
        // Adds each student to the vector with their studentIDs
        ans.push_back(name);
        ++it;
    }
    // Sorts the vector w.r.t. their last name
    sort(ans.begin(), ans.end());
    res += "[";
    // Loops through the vector and adss each element to the string
    for (int i = 0; i < ans.size(); ++i)
    {
        if (i == 0)
        {
            res += ans[i];
        }
        else
        {
            res += ", " + ans[i];
        }
    }
    res += "]";
    return res;
}
// Returns a sorted list of students enrolled in the course as a string
string University::getClassListByID(const string &courseNumber) const
{
    // Returns "[]" if courseNumber is invalid
    if (coursePointers.at(courseNumber) == 0)
    {
        return "[]";
    }
    vector<int> ids;
    string res;
    // Gets the course object from course container
    Course *c = coursePointers.at(courseNumber);
    auto it = c->studentList.begin();
    // Iterates through the course's student container
    while (it != c->studentList.end())
    {
        Student *s = c->studentList[(*it).first];
        int id;
        id = s->idOfStudent;
        // Adds each student's ID to the vector
        ids.push_back(id);
        ++it;
    }
    vector<string> ans;
    // Sorts the vector containing studentIDs
    sort(ids.begin(), ids.end());
    it = c->studentList.begin();
    int count = 0;
    string name;
    // Iterates through the studentList container & vector with studentIDs
    while (it != c->studentList.end() && count != ids.size())
    {
        // Gets the student object
        Student *s = c->studentList[(*it).first];
        name = s->getLastName(s->nameOfStudent) + ", " +
               s->getFirstName(s->nameOfStudent) + " (" + to_string(ids[count]) +
               ")";
        // Adds student's name & studentIDs to the vector
        ans.push_back(name);
        ++count;
        ++it;
    }
    // Iterates through the vector and adds each element to the string
    res += "[";
    for (int i = 0; i < ans.size(); ++i)
    {
        if (i == 0)
        {
            res += ans[i];
        }
        else
        {
            res += ", " + ans[i];
        }
    }
    res += "]";
    return res;
}
