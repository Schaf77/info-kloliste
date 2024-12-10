//
// Created by Oskar on 03.12.2024.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <cstdint>
#include <string>

using namespace std;


class Student {
public:
    Student(uint16_t& pNextFreeId, const string& name, const string& subject);
    [[nodiscard]] uint16_t getId() const;
    [[nodiscard]] const string& getName();
    [[nodiscard]] const string& getSubject();
    [[nodiscard]] bool getToiletState() const;
    [[nodiscard]] bool getQueuedState() const;
    void setToiletState(bool state);
    void setQueuedState(bool state);
private:
    uint16_t id;
    string name;
    string subject;
    bool isOnToilet;
    bool isQueued;
};



#endif //STUDENT_H
