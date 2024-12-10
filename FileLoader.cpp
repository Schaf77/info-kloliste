//
// Created by Oskar on 03.12.2024.
//

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include<regex>

#include "FileLoader.h"


using namespace std;

FileLoader::FileLoader() = default;

vector<Student> FileLoader::loadFile(const string& path) {
    // result map, where the key is the subject  and the element is a vector with all the students
    vector<Student> students;
    string line, subject, name;
    uint16_t nextFreeId = 0;

    // attempt to open file, throw exception when failed
    ifstream file(path);
    if (!file.is_open()) throw runtime_error("Could not open file");

    // read every line from file
    while (std::getline(file, line)) {
        // Ignore first Line ("Kurs,Name")
        if (line == "Kurs,Name") continue;

        // Split the line using stringstream and store the student
        stringstream ss(line);
        if (getline(ss, subject, ',') && getline(ss, name)) {
            // Save the student in the students vector
            Student student(&nextFreeId, name, subject);
            students.push_back(student);
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    return students;
}

vector<Student> FileLoader::loadExample() {
    uint16_t nextFreeId = 0;
    vector<Student> testStudents;
    Student testStudent01(&nextFreeId, "John", "MA L1");
    Student testStudent02(&nextFreeId, "Jane", "GE G1");
    Student testStudent03(&nextFreeId, "Peter", "SP G1");
    Student testStudent04(&nextFreeId, "Jens", "MA L1");
    Student testStudent05(&nextFreeId, "Klaus", "GE G1");
    Student testStudent06(&nextFreeId, "Klaus", "SP G1");
    Student testStudent07(&nextFreeId, "John", "MA L1");
    Student testStudent08(&nextFreeId, "Jane", "GE G1");
    Student testStudent09(&nextFreeId, "Peter", "SP G1");
    Student testStudent10(&nextFreeId, "Jens", "MA L1");
    Student testStudent11(&nextFreeId, "Klaus", "GE G1");
    Student testStudent12(&nextFreeId, "Klaus", "SP G1");


    testStudents.push_back(testStudent01);
    testStudents.push_back(testStudent02);
    testStudents.push_back(testStudent03);
    testStudents.push_back(testStudent04);
    testStudents.push_back(testStudent05);
    testStudents.push_back(testStudent06);
    testStudents.push_back(testStudent07);
    testStudents.push_back(testStudent08);
    testStudents.push_back(testStudent09);
    testStudents.push_back(testStudent10);
    testStudents.push_back(testStudent11);

    return testStudents;
}

vector<string> FileLoader::getSubjects(const vector<Student>& students) {
    vector<string> subjects;

    for (Student student : students) {
        const string subject = student.getSubject();
        if (ranges::find(subjects, subject) == subjects.end()) {
            subjects.push_back(subject);
        }
    }

    return subjects;
}

