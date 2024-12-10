//
// Created by Oskar on 03.12.2024.
//

#ifndef TOILETLIST_H
#define TOILETLIST_H

#include <queue>
#include <vector>
#include <string>
#include <map>
#include <qtypes.h>

#include "Student.h"
#include "json.hpp"


class ToiletList {
public:
    ToiletList();
    void init(const std::vector<Student>& students, const std::vector<std::string>& subjects);
    bool checkToiletAvailability(const std::string& subject);
    [[nodiscard]] nlohmann::json getStudentStatus(const uint16_t &id);
    [[nodiscard]] nlohmann::json getToiletStatus(const std::string& subject);
    [[nodiscard]] std::string getStudentStatusString(const uint16_t& id);
    [[nodiscard]] std::string getSubjectStatusString(const std::string& subject);
    void queueStudent(const uint16_t& id);
    void returnStudent(const uint16_t& id);
    void updateStudentToiletStatus(const uint16_t& id, const bool& isOnToilet);
    void updateStudentQueueStatus(const uint16_t& id, const bool& isQueued);
    [[nodiscard]] uint16_t getIdFromStudent(const std::string& name);
    Student* getStudentOnToilet(const std::string& subject);
private:
    std::map<std::string, std::queue<Student> > toiletQueueMap;   // students waiting to go on the toilet
    std::vector<Student> students;
    std::vector<std::string> subjects;
};

#endif //TOILETLIST_H
