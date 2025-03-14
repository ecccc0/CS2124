#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"

#ifndef REGISTRAR_H
#define REGISTRAR_H

namespace BrooklynPoly {
    class Registrar {
        friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
    public:
        Registrar();

        // Creates a new course, if none with that name
        bool addCourse(const std::string& courseName);
        // Creates a new student, if none with that name
        bool addStudent(const std::string& studentName);

        // If the student and the course exist, then enroll the student.
        bool enrollStudentInCourse(const std::string& studentName,
                                const std::string& courseName);

        // Unenroll the students from the course and remove the course
        // from the Registrar.
        bool cancelCourse(const std::string& courseName);

        // Get rid of everything!!!
        void purge();

    private:
        size_t findStudent(const std::string& studentName) const;
        size_t findCourse(const std::string& studentName) const;

        std::vector<Course*> courses;
        std::vector<Student*> students;
    }; // Registrar
}
#endif