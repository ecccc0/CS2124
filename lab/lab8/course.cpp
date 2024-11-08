#include <iostream>
#include <vector>
#include <string>
#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {
    ostream& operator<<(ostream& os, const Course& rhs)
    {
        os << rhs.getName() << ": ";
        if (rhs.students.empty())
        {
            os << "No students";
            return os;
        }
        for (Student* student : rhs.students)
        {
            os << student->getName() << " ";
        }
        return os;
    }
    Course::Course(const string& courseName) : name(courseName) {}

    const string& Course::getName() const {return name;}

    bool Course::addStudent(Student* student)
    {
        for (const Student* s : students)
        {
            if (s == student)
            {
                return false;
            }
        }
        students.push_back(student);
        return true;
    }

    void Course::removeStudentsFromCourse()
    {
        for (Student* student : students)
        {
            student->removedFromCourse(this);
        }
        students.clear();
    }
}
