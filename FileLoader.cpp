//
// Created by Oskar on 03.12.2024.
//

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <regex>

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
    while (getline(file, line)) {
        // Ignore first Line ("Kurs,Name")
        if (line == "Kurs,Name") continue;

        // Split the line using stringstream and store the student
        stringstream ss(line);
        if (getline(ss, subject, ',') && getline(ss, name)) {
            // Save the student in the students vector
            Student student(nextFreeId, name, subject);
            students.push_back(student);
        } else {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    return students;
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
