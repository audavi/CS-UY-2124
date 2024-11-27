/*
  Emily Lopez
  rec08_single.cpp
  Starter Code for required functionality
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

// course methods
ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ": ";
    if (rhs.students.size() == 0) {
        os << "No Students";
        return os;
    }
    for (size_t i = 0; i < rhs.students.size(); i++) {
        os << rhs.students[i]->getName() << " ";
    }
    return os;
}
Course::Course(const string& courseName) : name(courseName) {}
const string& Course::getName() const { return name; }
bool Course::addStudent(Student* rhs) { //names are unique
   bool studentFound = false;
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i] == rhs) {
            studentFound = true;
            break;
        }
    }
    if (studentFound) {
        return false;
    }
    students.push_back(rhs);
    return true;
}
void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); i++) {
        students[i]->removedFromCourse(this);
    }
    students.clear();
}

// student methods
ostream& operator<<(ostream& os, const Student& rhs) {
    os << rhs.getName() << ": ";
    if (rhs.courses.size() == 0) {
        os <<"No Courses";
        return os;
    }
    for (size_t i = 0; i < rhs.courses.size(); i++) {
        os << rhs.courses[i]->getName() << " ";
    }
    return os;
}
Student::Student(const string& name) : name(name) {}
const string& Student::getName() const { return name; }
bool Student::addCourse(Course* rhs) {
    courses.push_back(rhs);
    return true;
}
void Student::removedFromCourse(Course* rhs) {
    size_t shift = 0;
    for (size_t i = 0; i < courses.size(); i++) {
        if (courses[i] == rhs) {
            shift = i;
        }
        if (shift != courses.size()){
            courses[i] = courses[i+1];
        }
    }
    courses.pop_back();
}

//registrar methods
ostream& operator<<(ostream& os, const Registrar& rhs) {
    os << "Registrar's Report " << endl;
    os << "Courses: " << endl;
    for (size_t i = 0; i < rhs.courses.size(); i++) {
        os << *rhs.courses[i]  << endl;
    }
    os << "Students: " << endl;
    for (size_t i = 0; i < rhs.students.size(); i++) {
        os << *rhs.students[i] << endl;
    }
    return os;
}
Registrar::Registrar() {}
bool Registrar::addCourse(const string& rhs) {
    if (findCourse(rhs) == courses.size()) {
        courses.push_back(new Course(rhs));
        return true;
    }
    return false;
}
bool Registrar::addStudent(const string& rhs) {
    if (findStudent(rhs) == students.size()) {
        students.push_back(new Student(rhs));
        return true;
    }
    return false;
}
bool Registrar::enrollStudentInCourse(const string& studentName,
                               const string& courseName) {
    size_t courseInd = findCourse(courseName);
    size_t studentInd = findStudent(studentName);
    if (studentInd == students.size()) { //student doesnt exist
        return false;
    }
    if (courseInd == courses.size()) { // course doesnt exist
        return false;
    }
    Student* newStudent = students[studentInd];
    Course* newCourse = courses[courseInd];
    newStudent->addCourse(newCourse);
    newCourse->addStudent(newStudent);
    return true;
}
bool Registrar::cancelCourse(const string& courseName) {
    size_t courseInd = findCourse(courseName);
    if (courseInd == courses.size()){
        return false; // course doesnt exist
    }
    courses[courseInd]->removeStudentsFromCourse();
    delete courses[courseInd];

    for (size_t i = courseInd; i < courses.size()-1; i++) {
        courses[i] = courses[i+1];
    }
    courses.pop_back();
    return true;
}
void Registrar::purge() {
    for (size_t i = 0; i < students.size(); i ++){
        delete students[i];
    }
    students.clear();
    for (size_t i =0; i < courses.size(); i++) {
        delete courses[i];
    }
    courses.clear();
}
size_t Registrar::findStudent(const string& rhs) const {
    for (size_t i = 0; i < students.size(); i++){
        if (rhs == students[i]->getName()){
            return i;
        }
    }
    return students.size();
}
size_t Registrar::findCourse(const string& rhs) const {
    for (size_t i= 0; i < courses.size(); i++){
        if (rhs == courses[i]->getName()){
            return i;
        }
    }
    return courses.size();
}
