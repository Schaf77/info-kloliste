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
    void init(vector<Student> students, const vector<string>& subjects);
    bool checkToiletAvailability(const string& subject);
    [[nodiscard]] json getStudentStatus(uint16_t id) const;
    json getToiletStatus(string subject);
    void queueStudent(uint16_t id);
    void returnStudent(uint16_t id);
    void updateStudentToiletStatus(uint16_t id, bool isOnToilet);
    void updateStudentQueueStatus(uint16_t id, bool isQueued);
    uint16_t getIdFromStudent(const string& name);
private:
    map<string, queue<Student> > toiletQueueMap;   // students waiting to go on the toilet
    vector<Student> students;
};


#endif //TOILETLIST_H
