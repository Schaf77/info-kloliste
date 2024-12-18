//
// Created by Oskar on 08.12.2024.
//

#ifndef MAIN_H
#define MAIN_H

#include <string>

void queueStudent(const uint16_t& id);
void returnStudent(const uint16_t& id);
QString subjectStatus(const std::string& subject);
QString studentStatus(const uint16_t& student);
uint16_t getStudentId(const std::string& name);
std::vector<std::string> getSubjects();
bool getSubjectAvailability(const std::string& subject);
QString getStudentOnToilet(const std::string& subject);

#endif //MAIN_H
