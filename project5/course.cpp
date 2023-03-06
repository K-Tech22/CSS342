#include "course.h"
#include "student.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Constructor
Course::Course(const string &courseID, const string &courseName)
{
    nameofCourse = courseName;
    cID = courseID;
}
