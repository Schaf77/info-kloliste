//
// Created by Oskar on 03.12.2024.
//

#ifndef TOILETLIST_H
#define TOILETLIST_H
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <map>

#include "Student.h"
using namespace std;


class ToiletList {
public:
    ToiletList(vector<Student> students, const list<string>& subjects);
    bool checkToiletAvailability(const string& subject);
    json getStudentStatus(int id);
    void queueStudent(int id);
    void returnStudent(int id);
    void updateStudentToiletStatus(int id, bool isOnToilet);
private:
    map<string, queue<Student> > toiletQueueMap;   // students waiting to go on the toilet
    vector<Student> students;
};


#endif //TOILETLIST_H
