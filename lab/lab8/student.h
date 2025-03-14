#include <iostream>
#include <string>
#include <vector>


#ifndef STUDENT_H 
#define STUDENT_H

namespace BrooklynPoly {
    class Course;
    
    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const std::string& name);
        const std::string& getName() const;
        bool addCourse(Course* course);

        // Student method needed by Course::removeStudentsFromCourse
        void removedFromCourse(Course* course);

    private:
        std::string name;
        std::vector<Course*> courses;
    }; // Student


}
#endif
