/*
  rec08_single.cpp
  Lab 8
  Eric Cheung
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
    bool addStudent(Student* student);

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
    bool addCourse(Course* course);

    // Student method needed by Course::removeStudentsFromCourse
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
}; // Student

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();

    // Creates a new course, if none with that name
    bool addCourse(const string& courseName);
    // Creates a new student, if none with that name
    bool addStudent(const string& studentName);

    // If the student and the course exist, then enroll the student.
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);

    // Unenroll the students from the course and remove the course
    // from the Registrar.
    bool cancelCourse(const string& courseName);

    // Get rid of everything!!!
    void purge();

private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& studentName) const;

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

// course methods
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

// student methods
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

// registrar methods

Registrar::Registrar() {}

bool Registrar::addCourse(const string& courseName)
{
    if (findCourse(courseName) != courses.size())
    {
        return false;
    }
    courses.push_back(new Course(courseName));
    return true;
}

bool Registrar::addStudent(const string& studentName)
{
    if (findStudent(studentName) != students.size())
    {
        return false;
    }
    students.push_back(new Student(studentName));
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
    const string& courseName)
{
    size_t studentIndex = findStudent(studentName);
    size_t courseIndex = findCourse(courseName);
    if (studentIndex == students.size() || courseIndex == courses.size())
    {
        return false;
    }
    if (courses[courseIndex]->addStudent(students[studentIndex]) &&
        students[studentIndex]->addCourse(courses[courseIndex]))
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
    courses[courseIndex] = courses[courses.size() - 1];
    courses.pop_back();
    return true;
}

void Registrar::purge()
{
    for (size_t i = 0; i < courses.size(); ++i)
    {
        courses[i]->removeStudentsFromCourse();
        delete courses[i];
    }
    courses.clear();
    for (size_t i = 0; i < students.size(); ++i)
    {
        delete students[i];
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

ostream& operator<<(ostream& os, const Registrar& rhs)
{
    os << "Registrar's Report" << endl;
    os << "Courses: " << endl;
    for (size_t i = 0; i < rhs.courses.size(); ++i)
    {
        os << *rhs.courses[i] << endl;
    }
    os << "Students: " << endl;
    for (size_t i = 0; i < rhs.students.size(); ++i)
    {
        os << *rhs.students[i] << endl;
    }
    return os;
}