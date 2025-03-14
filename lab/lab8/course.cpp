#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {
    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const { return name; }

    bool Course::addStudent(Student* student)
    {
        for (size_t i = 0; i < students.size(); ++i)
        {
            if (students[i] == student)
            {
                return false;
            }
        }
        students.push_back(student);
        return true;
    }

    void Course::removeStudentsFromCourse()
    {
        for (size_t i = 0; i < students.size(); ++i)
        {
            students[i]->removedFromCourse(this);
        }
    }

    ostream& operator<<(ostream& os, const Course& rhs)
    {
        os << rhs.name << ": ";
        if (rhs.students.size() == 0)
        {
            os << "No Students";
        } else
        {
            for (size_t i = 0; i < rhs.students.size(); ++i)
            {
                os << rhs.students[i]->getName() << " ";
            }
        }
        return os;
    }

}