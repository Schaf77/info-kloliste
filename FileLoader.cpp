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


FileLoader::FileLoader() = default;

std::vector<Student> FileLoader::loadFile(const std::string& path) {
    // result map, where the key is the subject  and the element is a vector with all the students
    std::vector<Student> students;
    std::string line, subject, name;
    uint16_t nextFreeId = 0;

    // attempt to open file, throw exception when failed
    std::ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Could not open file");

    // read every line from file
    while (getline(file, line)) {
        // Ignore first Line ("Kurs,Name")
        if (line == "Kurs,Name") continue;

        // Split the line using stringstream and store the student
        std::stringstream ss(line);
        if (getline(ss, subject, ',') && getline(ss, name)) {
            // Save the student in the students vector
            Student student(nextFreeId, name, subject);
            students.push_back(student);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    return students;
}

std::vector<std::string> FileLoader::getSubjects(const std::vector<Student>& students) {
    std::vector<std::string> subjects;

    for (Student student : students) {
        const std::string subject = student.getSubject();
        if (std::ranges::find(subjects, subject) == subjects.end()) {
            subjects.push_back(subject);
        }
    }

    return subjects;
}
