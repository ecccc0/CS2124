#include <vector>
#include <iostream>
#include <string>
#include "registrar.h"
#include "course.h"
#include "student.h"

using namespace std;

namespace BrooklynPoly {
    Registrar::Registrar() {}

    ostream& operator<<(ostream& os, const Registrar& rhs)
    {
        os << "Registrar's Report" << endl;
        os << "Courses:\n";
        for (const Course* course : rhs.courses)
        {
            os << *course << " ";
        }
        os << endl;
        os << "Students:\n";
        for (const Student* student : rhs.students)
        {
            os << *student << " ";
        }
        return os;
    }
    bool Registrar::addCourse(const string& courseName)
    {
        for (const Course* course : courses)
        {
            if (course->getName() == courseName)
            {
                return false;
            }
        }
        courses.push_back(new Course(courseName));
        return true;
    }

    bool Registrar::addStudent(const string& studentName)
    {
        for (const Student* student : students)
        {
            if (student->getName() == studentName)
            {
                return false;
            }
        }
        students.push_back(new Student(studentName));
        return true;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName)
    {
        size_t studentIndex = findStudent(studentName);
        size_t courseIndex = findCourse(courseName);

        if (studentIndex == students.size() || courseIndex == courses.size())
        {
            return false;
        }

        if (students[studentIndex]->addCourse(courses[courseIndex]) && courses[courseIndex]->addStudent(students[studentIndex]))
        {
            return true;
        }
        return false;
    }

    bool Registrar::cancelCourse(const string& courseName)
    {
        size_t courseIndex = findCourse(courseName);
        if (courseIndex == courses.size())
        {
            return false;
        }
        courses[courseIndex]->removeStudentsFromCourse();
        delete courses[courseIndex];
        courses[courseIndex] = courses[courses.size()-1];
        courses.pop_back();
        return true;
    }

    void Registrar::purge()
    {
        for (Course* course : courses)
        {
            course->removeStudentsFromCourse();
            delete course;
        }
        courses.clear();

        for (Student* student : students)
        {
            delete student;
        }
        students.clear();
    }

    size_t Registrar::findStudent(const string& studentName) const
    {
        for (size_t i = 0; i < students.size(); ++i)
        {
            if (students[i]->getName() == studentName)
            {
                return i;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const string& courseName) const
    {
        for (size_t i = 0; i < courses.size(); ++i)
        {
            if (courses[i]->getName() == courseName)
            {
                return i;
            }
        }
        return courses.size();
    }
}