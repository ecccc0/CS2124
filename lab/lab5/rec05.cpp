/*
Eric Cheung
Lab 5
rec05.cpp
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
public:
  Section(const string& sectionName, const string& dayOfWeek, int hour) :
    sectionName(sectionName), timeSlot(dayOfWeek, hour) {}
  ~Section() {
    cout << "Section " << sectionName << " is being deleted" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
      cout << "Deleting " << students[i]->getStudentName() << endl;
      delete students[i];
    }
  }
  Section(const Section& rhs) : sectionName(rhs.sectionName) , timeSlot(rhs.timeSlot){
    for (size_t i = 0; i < rhs.students.size(); ++i) {
      students.push_back(new StudentRecord(*(rhs.students[i])));
    }
  }
  friend ostream& operator<<(ostream& os, const Section& section);
  void addStudent(const string& studentName) {
    students.push_back(new StudentRecord(studentName));
  }
  void addGrade(const string& studentName, int grade, int week) {
    for (size_t i = 0; i < students.size(); ++i) {
      if (students[i]->getStudentName() == studentName) {
        students[i]->setGrade(grade, week);
        return;
    }
  }
}
private:

  class StudentRecord {
  public:
    StudentRecord(const string& studentName) :
      studentName(studentName), grades(vector<int>(14, -1)) {}
    friend ostream& operator<<(ostream& os, const StudentRecord& studentRecord);
    const string& getStudentName() const {
      return studentName;
    }
    void setGrade(int grade, int week) {
      grades[week - 1] = grade;
    }

  private:
    string studentName;
    vector<int> grades;
  };

  class TimeSlot {
  public:
    TimeSlot(const string& dayOfWeek, int hour) :
      dayOfWeek(dayOfWeek), hour(hour) {}
    friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot);
  private:
      string dayOfWeek;
      int hour;
  };
  friend ostream& operator<<(ostream& os, const Section::StudentRecord& studentRecord);

  friend ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot);
string sectionName;
TimeSlot timeSlot;
vector<StudentRecord*> students;
};

class LabWorker {
public:
  LabWorker(const string& name) : name(name), section(nullptr) {}
  void addSection(Section& section) {
    this->section = &section;
  }
  void addGrade(const string& studentName, int grade, int week) {
    section->addGrade(studentName, grade, week);
  }
  friend ostream& operator<<(ostream& os, const LabWorker& labWorker);
private:
  string name;
  Section* section;
};


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

ostream& operator<<(ostream& os, const Section& section) {
  os << "Section: " << section.sectionName << ", Time slot: [" 
  << section.timeSlot << "], Students:";
  if (section.students.size() == 0) {
    os << " None";
    return os;
  }
  os << endl;

  for (size_t i = 0; i < section.students.size(); ++i) {
    os << *section.students[i] << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const Section::StudentRecord& studentRecord) {
  os << "Name: " << studentRecord.studentName << ", Grades: ";
  for (size_t i = 0; i < studentRecord.grades.size(); ++i) {
    os << studentRecord.grades[i] << " ";
  }
  return os;
}

ostream& operator<<(ostream& os, const Section::TimeSlot& timeSlot) {
  string AM_PM = timeSlot.hour < 12 ? "AM" : "PM";

  os << "Day: " << timeSlot.dayOfWeek << ", Start time: " 
    << timeSlot.hour % 12 << AM_PM; 
  return os;
}

ostream& operator<<(ostream& os, const LabWorker& labWorker) {
  os << labWorker.name;
  if (labWorker.section != nullptr) {
    os << " has " << *labWorker.section;
  } else {
    os << " does not have a section";
  }
  return os;
}