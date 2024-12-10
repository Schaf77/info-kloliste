//
// Created by Oskar on 03.12.2024.
//

#ifndef FILELOADER_H
#define FILELOADER_H
#include <string>
#include <vector>

#include "Student.h"

using namespace std;

class FileLoader {
public:
    FileLoader();
    [[nodiscard]] static vector<Student> loadFile(const string& path);
    [[nodiscard]] static vector<Student> loadExample();
    [[nodiscard]] static vector<string> getSubjects(const vector<Student>& students);
};



#endif //FILELOADER_H
