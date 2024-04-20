#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <memory>
#include <vector>
#include <map>
using namespace std;

class Course {
public:
    int assignment;
    int test;
    int exam;

    Course(int a = 0, int t = 0, int e = 0) : assignment(a), test(t), exam(e) {}
};

class Semester {
public:
    vector<Course> courses;

    Semester(int courseCount = 0) {
        courses.resize(courseCount, Course());
    }

    void addCourse(const Course& course) {
        courses.push_back(course);
    }
};

class Student {
protected:
    string name;
    int score;
    string schoolName;
    string dob;
    string courseName;
    vector<Semester> semesters;

public:
    Student(string nm, int sc, string school, string db, string course, int semesterCount)
        : name(move(nm)), score(sc), schoolName(move(school)), dob(move(db)), courseName(move(course)), semesters(semesterCount) {}

    // No need for destructor as vector handles its memory.

    virtual void doAssignment() {
        cout << "Student name: " << name << " with schoolName: " << schoolName << " Day of birth: " << dob << " courseName: " << courseName << endl;
        cout << " is doing assignment" << endl;
        score += (rand() % 101) * 3;
    }

    virtual void takeTest() {
        cout << "Student name: " << name << " with schoolName: " << schoolName << " Day of birth: " << dob << " courseName: " << courseName << endl;
        cout << " is doing test" << endl;
        score += (rand() % 101) * 2;
    }

    virtual void takeExam() {
        cout << "Student name: " << name << " with schoolName: " << schoolName << " Day of birth: " << dob << " courseName: " << courseName << endl;
        cout << " is doing Exam" << endl;
        score += (rand() % 101) * 5;
    }

    virtual void calculateScore() {
        for (auto& semester : semesters) {
            for (auto& course : semester.courses) {
                doAssignment();
                takeTest();
                takeExam();
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Student& obj) {
        os << "Name of student is " << obj.name << " | Score of student is " << obj.score << endl;
        return os;
    }
};

class UniStudent : public Student {
public:
    UniStudent(string nm, int sc, string school, string db, string course)
        : Student(move(nm), sc, move(school), move(db), move(course), 8) {
        for (auto& semester : semesters) {
            semester.courses = { Course(3, 2, 1), Course(3, 2, 1), Course(3, 2, 1), Course(3, 2, 1) };
        }
    }
};

class CollegeStudent : public Student {
public:
    CollegeStudent(string nm, int sc, string school, string db, string course)
        : Student(move(nm), sc, move(school), move(db), move(course), 4) {
        for (auto& semester : semesters) {
            semester.courses = { Course(1, 1, 1), Course(1, 1, 1), Course(1, 1, 1) };
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(0)));

    map<string, unique_ptr<Student>> studentsMap;

    studentsMap["Steve"] = make_unique<UniStudent>("Steve", 100, "MIT", "1995-12-12", "Computer Science");
    studentsMap["John"] = make_unique<CollegeStudent>("John", 100, "Harvard", "1991-12-12", "Computer Engineering");

    for (auto& pair : studentsMap) {
        pair.second->calculateScore();
        cout << *pair.second;
    }

    return 0;
}
