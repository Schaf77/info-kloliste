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
    ToiletList(vector<Student> students, const vector<string>& subjects);
    bool checkToiletAvailability(const string& subject);
    [[nodiscard]] json getStudentStatus(int id) const;
    json getToiletStatus(string subject);
    void queueStudent(int id);
    void returnStudent(int id);
    void updateStudentToiletStatus(int id, bool isOnToilet);
    void updateStudentQueueStatus(int id, bool isQueued);
private:
    map<string, queue<Student> > toiletQueueMap;   // students waiting to go on the toilet
    vector<Student> students;
};


#endif //TOILETLIST_H
