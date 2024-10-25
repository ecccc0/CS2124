/*
Eric Cheung
Lab8
rec08.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);

    // Tell the students that they are no longer in the course
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
}; // Course

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
}; // Student

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string&);
    // Creates a new student, if none with that name
    bool addStudent(const string&);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
}; // Registrar

int main()
{

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
} // main

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

ostream& operator<<(ostream& os, const Course& rhs)
{
    os << rhs.getName() << ": ";
    if (rhs.students.empty())
    {
        os << "No students";
        return os;
    }
    for (const Student* student : rhs.students)
    {
        os << student->getName() << " ";
    }
    return os;
}

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


Course::Course(const string& courseName) : name(courseName) {}

const string& Course::getName() const {return name;}

bool Course::addStudent(Student* student)
{
    for (Student* s : students)
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

Student::Student(const string& studentName) : name(studentName) {}

const string& Student::getName() const {return name;}

bool Student::addCourse(Course* course)
{
    for (Course* c : courses)
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

Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName)
{
    for (Course* course : courses)
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
    for (Student* student : students)
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
