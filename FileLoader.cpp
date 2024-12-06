//
// Created by Oskar on 03.12.2024.
//

#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>
#include<regex>

#include "FileLoader.h"


using namespace std;

FileLoader::FileLoader() {
    nextFreeId = 0;
}

map<string, vector<string>> FileLoader::loadFile(const string& path) {
    // result map, where the key is the subject abbreviation and the element is a vector with all the students
    map<string, vector<string>> data;
    string line;

    // Define the regular expression pattern to match the subject line
    regex pattern("^[A-Z]{2}.*");

    // attempt to open file, throw exception when failed
    ifstream file(path);
    if (!file.is_open()) throw std::runtime_error("Could not open file");

    // read every line from file
    while (std::getline(file, line)) {
        // TODO analyse file
        cout << line << endl;
    }

    return data;
}

vector<Student> FileLoader::loadExample() {
    nextFreeId = 0;
    vector<Student> testStudents;
    Student testStudent01(&nextFreeId, "John", "Maths");
    Student testStudent02(&nextFreeId, "Jane", "English");
    Student testStudent03(&nextFreeId, "Peter", "German");
    Student testStudent04(&nextFreeId, "Jens", "Maths");
    Student testStudent05(&nextFreeId, "Klaus", "English");
    Student testStudent06(&nextFreeId, "Klaus", "German");
    Student testStudent07(&nextFreeId, "John", "Maths");
    Student testStudent08(&nextFreeId, "Jane", "English");
    Student testStudent09(&nextFreeId, "Peter", "German");
    Student testStudent10(&nextFreeId, "Jens", "Maths");
    Student testStudent11(&nextFreeId, "Klaus", "English");
    Student testStudent12(&nextFreeId, "Klaus", "German");


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

