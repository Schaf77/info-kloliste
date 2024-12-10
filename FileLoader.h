//
// Created by Oskar on 03.12.2024.
//

#ifndef FILELOADER_H
#define FILELOADER_H
#include <string>
#include <vector>

#include "Student.h"

class FileLoader {
public:
    FileLoader();
    [[nodiscard]] static std::vector<Student> loadFile(const std::string& path);
    [[nodiscard]] static std::vector<std::string> getSubjects(const std::vector<Student>& students);
};

#endif //FILELOADER_H
