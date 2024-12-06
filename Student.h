//
// Created by Oskar on 03.12.2024.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;


class Student {
public:
    Student(int *pNextFreeId, const string &name, const string &subject);
    int getId();
    string getName();
    string getSubject();
    bool getToiletState();
    bool getQueuedState();
    void setToiletState(bool state);
    void setQueuedState(bool state);
private:
    int id;
    string name;
    string subject;
    bool isOnToilet;
    bool isQueued;
};



#endif //STUDENT_H
