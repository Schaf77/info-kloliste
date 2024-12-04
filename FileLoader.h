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
    map<string, vector<string>> loadFile(const string& path);
    vector<Student> loadExample();
private:
    int nextFreeId;
};



#endif //FILELOADER_H
