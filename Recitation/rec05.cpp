/*
  Emily Lopez
  rec05.cpp
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    class TimeSlot;
    class StudentRecords;
    friend ostream& operator<<(ostream& os, const Section& theSection);
    friend ostream& operator<<(ostream& os, const Section::StudentRecords& theStudent);
    friend ostream& operator<<(ostream& os, const TimeSlot& labTimeSlot);
    class StudentRecords {
    public:
        friend ostream& operator<<(ostream& os, const Section::StudentRecords& theStudent);
        //every student is absent each week before the grade is entered
        StudentRecords(const string& studentName)
        : studentName(studentName), gradeRecords(14, -1) {}
        const string& getStudentName() const {return studentName;}

        void updateGrade(int newGrade, const int week){
            if ((week >= 1) && (week - 1 <= gradeRecords.size())){
                gradeRecords[week - 1] = newGrade;
            }
        }

    private:
        string studentName; // no two students can have the same name
        vector<int> gradeRecords;

    };
    class TimeSlot {
    public:
        friend ostream& operator<<(ostream& os, const TimeSlot& labTimeSlot);
        TimeSlot(const string& day, const unsigned hour): day(day), hour(hour) {}
    private:
        string day;
        unsigned hour;
    };

public:
    //constructor
    Section(const string& sectionName, const string& dayOfWeek, const unsigned time)
    : sectionName(sectionName), labTimeSlot(dayOfWeek, time) {}
    //copt constructor
    Section(const Section& anotherSection) : sectionName(anotherSection.sectionName), labTimeSlot(anotherSection.labTimeSlot) {
        for (size_t i = 0; i < anotherSection.records.size(); i++) {
            records.push_back(new StudentRecords(*(anotherSection.records[i])));
        }
    }
    //destructor
    ~Section() {
        cout << "Section " << sectionName << " is being deleted" << endl;
        for (size_t i = 0; i < records.size(); i++) {
            cout << "Deleting " << records[i]->getStudentName() << endl;
            delete records[i];
        }
    }
    void addStudent(const string& studentName) {
        StudentRecords* newStudent = new StudentRecords(studentName);
        records.emplace_back(newStudent);
    }


    void addGrade(const string& studentName, int grade, int week) {
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i]->getStudentName() == studentName) {
                records[i]->updateGrade(grade, week);
            }
        }
    }
    void reuseSection() {
        cout << "Section " << sectionName << " is being deleted\n";
        for (size_t i = 0; i < records.size(); i++) {
            cout << "Deleting " << records[i]->getStudentName();
           delete records[i];
        }
        records.clear();
    }

private:
    string sectionName;
    TimeSlot labTimeSlot;
    vector <StudentRecords*> records; // students are in the heap
};

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& theWorker);
public:
    // constructor
    LabWorker(const string& name) : workerName(name) {}
    // add section to the lab instructor
    void addSection(Section& sectionName) { sectionPtr = &sectionName; }
    //enter grades for their students each week
    void addGrade(const string& studentName, int grade, int week){
        sectionPtr->addGrade(studentName, grade, week);
    }
private:
    string workerName;
    Section* sectionPtr = nullptr;
};

ostream& operator<<(ostream& os, const Section::StudentRecords& theStudent) {
    os << "Name: " << theStudent.studentName << ", Grades: ";
    for (size_t i = 0; i < theStudent.gradeRecords.size(); i++) {
        os << theStudent.gradeRecords[i] << " ";
    }
    return os;
}
ostream& operator<<(ostream& os, const Section::TimeSlot& labTimeSlot) {
    if (labTimeSlot.hour > 12) {
        os << "Time slot: [Day: " << labTimeSlot.day <<
            ", Start time: " << labTimeSlot.hour - 12 << "pm]";
    } else {
        os << "Time slot: [Day: " << labTimeSlot.day <<
            ", Start time: " << labTimeSlot.hour << "am]";
    }
    return os;
}



ostream& operator<<(ostream& os, const Section& section){
    os << "Section " << section.sectionName << ", " << section.labTimeSlot << ", ";
    if (section.records.empty()){
        os << "Students: None " << endl;
    }
    else{
        os << "Students: " << endl;
        for (size_t i = 0; i < section.records.size(); i++){
            os << *(section.records[i]) << endl;
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const LabWorker& theWorker) {
    os << theWorker.workerName;
    if (theWorker.sectionPtr == nullptr) {
        os << " does not have a section" << endl;
    } else {
        os << " has Section: " << (*theWorker.sectionPtr) << endl;
    }
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
