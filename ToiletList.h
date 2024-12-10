//
// Created by Oskar on 03.12.2024.
//

#ifndef TOILETLIST_H
#define TOILETLIST_H
#include <queue>
#include <vector>
#include <string>
#include <map>

#include "Student.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;


class ToiletList {
public:
    ToiletList();
    void init(const vector<Student>& students, const vector<string>& subjects);
    bool checkToiletAvailability(const string& subject);
    [[nodiscard]] json getStudentStatus(const uint16_t &id);
    [[nodiscard]] json getToiletStatus(const string& subject);
    [[nodiscard]] string getStudentStatusString(const uint16_t& id);
    [[nodiscard]] string getSubjectStatusString(const string& subject);
    void queueStudent(const uint16_t& id);
    void returnStudent(const uint16_t& id);
    void updateStudentToiletStatus(const uint16_t& id, const bool& isOnToilet);
    void updateStudentQueueStatus(const uint16_t& id, const bool& isQueued);
    [[nodiscard]] uint16_t getIdFromStudent(const string& name);
    Student* getStudentOnToilet(const string& subject);
private:
    map<string, queue<Student> > toiletQueueMap;   // students waiting to go on the toilet
    vector<Student> students;
    vector<string> subjects;
};


#endif //TOILETLIST_H
