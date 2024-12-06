//
// Created by Oskar on 03.12.2024.
//

#include "Student.h"

Student::Student(int *pNextFreeId, const string &name, const string &subject) {
    // assign next available id and increment the nextFreeId variable
    this->id = *(pNextFreeId);
    (*pNextFreeId)++;

    // set toilet status
    this->isOnToilet = false;
    this->isQueued = false;

    // set example values
    this->name = name;
    this->subject = subject;
}

int Student::getId() {
    return this->id;
}

string Student::getSubject() {
    return this->subject;
}

string Student::getName() {
    return this->name;
}
bool Student::getToiletState() {
    return this->isOnToilet;
}

bool Student::getQueuedState() {
    return this->isQueued;
}

void Student::setToiletState(bool state) {
    this->isOnToilet = state;
}

void Student::setQueuedState(bool state) {
    this->isQueued = state;
}
