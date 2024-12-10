//
// Created by Oskar on 03.12.2024.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <cstdint>
#include <string>

class Student {
public:
    Student(uint16_t& pNextFreeId, const std::string& name, const std::string& subject);
    [[nodiscard]] uint16_t getId() const;
    [[nodiscard]] const std::string& getName();
    [[nodiscard]] const std::string& getSubject();
    [[nodiscard]] bool getToiletState() const;
    [[nodiscard]] bool getQueuedState() const;
    void setToiletState(bool state);
    void setQueuedState(bool state);
private:
    uint16_t id;
    std::string name;
    std::string subject;
    bool isOnToilet;
    bool isQueued;
};

#endif //STUDENT_H
