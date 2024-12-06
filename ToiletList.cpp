//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include <list>
#include "ToiletList.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

ToiletList::ToiletList(vector<Student> students, const vector<string>& subjects) {
    this->students = std::move(students);

    for (const string& subject : subjects) {
        toiletQueueMap.at(subject) = queue<Student>();
    }
}

// returns true if toilet is available for subject
bool ToiletList::checkToiletAvailability(const string& subject) {
    for (Student student : this->students) {
        if (student.getSubject() == subject && student.getToiletState())
            return false;
    }
    return true;
}

void ToiletList::updateStudentToiletStatus(const int id, const bool isOnToilet) {
    students.at(id).setToiletState(isOnToilet);
}

json ToiletList::getStudentStatus(const int id) {
    Student student = students.at(id);

    json output = {
        {"name", student.getName()},
        {"subject", student.getSubject()},
        {"isQueued", student.getQueuedState()}
    };

    return students.at(id).getToiletState();
}

json ToiletList::getToiletStatus(string subject) {

    json output = {
        {"subject", subject},
        {"availability", checkToiletAvailability(subject)},
        {"queueLength", toiletQueueMap.at(subject).size()}
    };
}


void ToiletList::queueStudent(const int id) {
    try {
        Student student = students.at(id);

        // check if student is already queued or on the toilet
        if (student.getQueuedState() && student.getToiletState()) return;

        // send the student to the toilet, if it's available
        if (checkToiletAvailability(student.getSubject())) {
            updateStudentToiletStatus(id, true);
        } else {
            // otherwise queue the student in his subject's queue
            toiletQueueMap.at(student.getSubject()).push(student);
            student.setQueuedState(true);
        }
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
    }
}


void ToiletList::returnStudent(const int id) {
    const string subject = students.at(id).getSubject();
    updateStudentToiletStatus(id, false);

    if (!toiletQueueMap.at(subject).empty()) {

        // get the next student in line
        Student nextStudent = toiletQueueMap.at(subject).front();
        // send the student to the toilet
        updateStudentToiletStatus(nextStudent.getId(), true);
        // remove the student from the queue
        toiletQueueMap.at(subject).pop();
        // remove the student from the queue
        nextStudent.setQueuedState(false);
    }
}
