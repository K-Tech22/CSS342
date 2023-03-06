
#include "enrollmentsystem.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

// check enrollment system
void test1()
{
    EnrollmentSystem es;
    assert(es.addUniversity("UWB"));
    assert(!es.addUniversity("UWB"));
    assert(es.addUniversity("UW Seattle"));
    assert(es.addUniversity("UW Tacoma"));
    assert(!es.setCurrentUniversity("UWx"));
    assert(es.setCurrentUniversity("UWB"));
    assert(es.getUniversityName() == "UWB");
    // read data
    assert(es.readCourseList("data-courses.txt"));
    assert(es.readStudentList("data-students.txt"));
    assert(es.readEnrollmentInfo("data-enrollments.txt"));
    // check courses
    assert(!es.addCourse(999, "CSS342"));
    assert(!es.addCourse(1070, "CSS3422"));
    assert(!es.isInCourse(1070, "CSS342"));
    assert(es.addCourse(1070, "CSS342"));
    assert(es.dropCourse(1070, "CSS343"));
    assert(es.getCourseTitle("CSS342") ==
           "Data Structures, Algorithms, and Discrete Mathematics I");
    // check enrollments
    assert(es.getEnrolledCourses(1070) == "[CSS110, CSS173, CSS342]");
    string c342byLastName =
        "[Collins, Cassandra (1070), Evans, Juan (1401), Gonzalez, Holly (1223), "
        "Henderson, Daniel (1364), Taylor, Alexander (1986), Thompson, Christine "
        "(1386), Watson, Alex (1211)]";
    assert(es.getClassListByLastName("CSS342") == c342byLastName);
    string c342byID =
        "[Collins, Cassandra (1070), Watson, Alex (1211), Gonzalez, Holly "
        "(1223), Henderson, Daniel (1364), Thompson, Christine (1386), Evans, "
        "Juan (1401), Taylor, Alexander (1986)]";
    assert(es.getClassListByID("CSS342") == c342byID);
}

// run all tests
int main()
{
    test1();

    cout << "Done." << endl;
}
