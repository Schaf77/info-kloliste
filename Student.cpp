//
// Created by Oskar on 03.12.2024.
//

#include "Student.h"

Student::Student(uint16_t& pNextFreeId, const std::string& name, const std::string& subject) {
    // assign next available id and increment the nextFreeId variable
    this->id = pNextFreeId;
    pNextFreeId++;

    // set toilet status
    this->isOnToilet = false;
    this->isQueued = false;

    // set example values
    this->name = name;
    this->subject = subject;
}

uint16_t Student::getId() const {
    return this->id;
}

const std::string& Student::getSubject() {
    return this->subject;
}

const std::string& Student::getName() {
    return this->name;
}
bool Student::getToiletState() const {
    return this->isOnToilet;
}

bool Student::getQueuedState() const {
    return this->isQueued;
}

void Student::setToiletState(const bool state) {
    this->isOnToilet = state;
}

void Student::setQueuedState(const bool state) {
    this->isQueued = state;
}
