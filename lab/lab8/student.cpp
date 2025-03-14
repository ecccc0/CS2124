#include <iostream>
#include <string>
#include <vector>

#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly {
    Student::Student(const string& studentName) : name(studentName) {}

    const string& Student::getName() const { return name; }

    bool Student::addCourse(Course* course)
    {
        for (size_t i = 0; i < courses.size(); ++i)
        {
            if (courses[i] == course)
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
                courses[i] = courses[courses.size() - 1];
                courses.pop_back();
                return;
            }
        }
    }

    ostream& operator<<(ostream& os, const Student& rhs)
    {
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0)
        {
            os << "No Courses";
        } else
        {
            for (size_t i = 0; i < rhs.courses.size(); ++i)
            {
                os << rhs.courses[i]->getName() << " ";
            }
        }
        return os;
    }
}