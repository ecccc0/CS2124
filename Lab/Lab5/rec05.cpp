/*
  rec05.cpp
  Lab 5
  Eric CHeung
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Section{
    class TimeSlot{
        friend ostream &operator<<(ostream &os, const TimeSlot &timeSlot);
        public:
            TimeSlot(const string& day, unsigned int hour): day(day), hour(hour){}

            const string& getDay() const {return day;}
            unsigned int getHour() const {return hour;}
        private:
            string day;
            unsigned int hour;
    };

    class StudentRecord{
        friend ostream &operator<<(ostream &os, const StudentRecord &studentRecord);
        public:
            
            StudentRecord(const string& name) : name(name), grade(vector<int>(14, -1)) {}

            ~StudentRecord(){
                cout << "Deleting " << name << endl;
            }

            StudentRecord(StudentRecord& sr){
                name = sr.name;
                grade = sr.grade;
            }

            const string& getName() const {return name;}

            void setGrade(int grade, int week){
                this->grade[week-1] = grade;
            }
        private:
            string name;
            vector<int> grade;
    };

    friend ostream &operator<<(ostream &os, const Section &sec);
    friend ostream &operator<<(ostream &os, const Section::TimeSlot &timeSlot);
    friend ostream &operator<<(ostream &os, const Section::StudentRecord &studentRecord);

    TimeSlot timeSlot;
    vector<StudentRecord*> students;
    string name;

    public:
    Section(const string& name, const string& day, unsigned int hour): name(name), timeSlot(day, hour){}
    ~Section(){
        for (size_t i = 0; i < students.size(); i++){
            delete students[i];
            students[i] = nullptr;
        }
    }
    Section(const Section& s) : name(s.name), timeSlot(s.timeSlot){
        name = s.name;
        timeSlot = s.timeSlot;
        for (size_t i = 0; i < s.students.size(); i++){
            students.push_back(new StudentRecord(*(s.students[i])));
        }
    }
    const string& getName() const {return name;}

    void addGrade(const string& studentName, int grade, int week){
        for (size_t i = 0; i < students.size(); i++){
            if (students[i]->getName() == studentName){
                students[i]->setGrade(grade, week);
                return;
            }
        }
        cout << "Student not found!" << endl;
    }


    void addStudent(const string& name){
        students.push_back(new StudentRecord(name));
    }
};

class LabWorker{
    friend ostream &operator<<(ostream &os, const LabWorker &labWorker);
    public:
        LabWorker(const string& name): name(name), section(nullptr){}
        void addSection(Section& sec){
            section = &sec;
        }
        void addGrade(const string& studentName, int grade, int week) {
            section->addGrade(studentName, grade, week);
        }
    private:
        string name;
        Section* section;
};

ostream &operator<<(ostream &os, const Section &sec){
    os << "Section: " << sec.getName() << " ";
    os << (sec.timeSlot) << endl;
    os << "Students: ";
    if (sec.students.size() == 0){
        os << "None" << endl;
        return os;
    }
    os << endl;
    for (size_t i = 0; i < sec.students.size(); i++){
        os << *(sec.students[i]) << endl;
    }
    return os;
}

ostream &operator<<(ostream &os, const Section::TimeSlot &timeSlot){
    string AM_PM = timeSlot.getHour() < 12 ? "am" : "pm";
    os << "Time slot: [Day: " << timeSlot.getDay() << ", Start time " << timeSlot.getHour()%12 << AM_PM << "]";
    return os;
}


ostream &operator<<(ostream &os, const Section::StudentRecord &studentRecord){
    os << "Student: " << studentRecord.getName() << " Grades: ";
    for (size_t i = 0; i < studentRecord.grade.size(); i++){
        os << (studentRecord.grade)[i] << " ";
    }
    return os;
}

ostream &operator<<(ostream &os, const LabWorker &labWorker){
    os << "Lab Worker: " << labWorker.name << endl;
    if (!labWorker.section){
        os << labWorker.name << " does not have a section" << endl;
        return os;
    }
    os << labWorker.name << " has section " << *(labWorker.section);
    return os;
}

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main
