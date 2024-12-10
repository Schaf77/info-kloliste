//
// Created by Oskar on 08.12.2024.
//

#ifndef MAIN_H
#define MAIN_H

#include <string>
#include "json.hpp"

using namespace std;

void queueStudent(const uint16_t& id);
void returnStudent(const uint16_t& id);
QString subjectStatus(const string& subject);
QString studentStatus(const uint16_t& student);
uint16_t getStudentId(const string& name);
QString jsonToString(const nlohmann::json& jsonObj);
vector<QString> jsonStudentStatusToString(const nlohmann::json& jsonObj);
vector<QString> jsonSubjectStatusToString(const nlohmann::json& jsonObj);
vector<string> getSubjects();
bool getSubjectAvailability(const string& subject);
QString getStudentOnToilet(const string& subject);

#endif //MAIN_H
