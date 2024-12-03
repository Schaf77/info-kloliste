//
// Created by Oskar on 03.12.2024.
//

#include "Student.h"

Student::Student(int *pNextFreeId, const string &lastName, const string &firstName, const string &subject) {
    // assign next available id and increment the nextFreeId variable
    this->id = *(pNextFreeId);
    (*pNextFreeId)++;

    // set toilet status
    this->isOnToilet = false;

    // set example values
    this->lastName = lastName;
    this->firstName = firstName;
    this->subject = subject;
}

int Student::getId() {
    return this->id;
}

string Student::getSubject() {
    return this->subject;
}

string Student::getFirstName() {
    return this->firstName;
}

string Student::getLastName() {
    return this->lastName;
}

bool Student::getToiletState() {
    return this->isOnToilet;
}

void Student::setToiletState(bool state) {
    this->isOnToilet = state;
}
