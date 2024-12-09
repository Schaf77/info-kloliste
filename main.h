//
// Created by Oskar on 08.12.2024.
//

#ifndef MAIN_H
#define MAIN_H

#include <string>
#include "json.hpp"

void queueStudent(const uint16_t& id);
void returnStudent(const uint16_t& id);
QString subjectStatus(const std::string& subject);
QString studentStatus(const uint16_t& student);
uint16_t getStudentId(const std::string& name);
QString jsonToString(const nlohmann::json& jsonObj);
std::vector<QString> jsonStudentStatusToString(const nlohmann::json& jsonObj);
std::vector<QString> jsonSubjectStatusToString(const nlohmann::json& jsonObj);

#endif //MAIN_H
