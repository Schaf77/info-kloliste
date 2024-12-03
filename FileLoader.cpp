//
// Created by Oskar on 03.12.2024.
//

#include "FileLoader.h"
FileLoader::FileLoader() {
    nextFreeId = 0;
}

void FileLoader::loadFile(const string& path) {
}

vector<Student> FileLoader::loadExample() {
    nextFreeId = 0;
    vector<Student> testStudents;
    Student testStudent01(&nextFreeId, "John", "Doe", "Maths");
    Student testStudent02(&nextFreeId, "Jane", "Doe", "English");
    Student testStudent03(&nextFreeId, "Peter", "Doe", "German");
    Student testStudent04(&nextFreeId, "Jens", "Doe", "Maths");
    Student testStudent05(&nextFreeId, "Klaus", "Doe", "English");
    Student testStudent06(&nextFreeId, "Klaus", "Doe", "German");
    Student testStudent07(&nextFreeId, "John", "Doe", "Maths");
    Student testStudent08(&nextFreeId, "Jane", "Doe", "English");
    Student testStudent09(&nextFreeId, "Peter", "Doe", "German");
    Student testStudent10(&nextFreeId, "Jens", "Doe", "Maths");
    Student testStudent11(&nextFreeId, "Klaus", "Doe", "English");
    Student testStudent12(&nextFreeId, "Klaus", "Doe", "German");


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

