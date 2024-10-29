#include <iostream>
#include <string>
#include <vector>
#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Student& rhs)
    {
        os << rhs.getName() << ": ";
        if (rhs.courses.empty())
        {
            os << "No courses";
            return os;
        }

        for (const Course* course : rhs.courses)
        {
            os << course->getName() << " ";
        }
        return os;
    }
    
    Student::Student(const string& studentName) : name(studentName) {}

    const string& Student::getName() const {return name;}

    bool Student::addCourse(Course* course)
    {
        for (const Course* c : courses)
        {
            if (c == course)
            {
                return false;
            }
        }
        courses.push_back(course);
        return true;
    }

    void Student::removedFromCourse(Course* course)
    {
        for (size_t i = 0; i < courses.size(); ++i)
        {
            if (courses[i] == course)
            {
                courses[i] = courses[courses.size()-1];
                courses.pop_back();
                return;
            }
        }
    }
}