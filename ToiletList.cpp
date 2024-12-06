//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include <list>

#include "ToiletList.h"
#include "json.hpp"

using json = nlohmann::json;

ToiletList::ToiletList(vector<Student> students, const list<string>& subjects) {
    this->students = std::move(students);

    for (const string& subject : subjects) {
        toiletQueueMap[subject] = queue<Student>();
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
    students[id].setToiletState(isOnToilet);
}

json ToiletList::getStudentStatus(const int id) {
    Student student = students[id];

    json output = {
        {"name", student.getName()},
        {"subject", student.getSubject()},
        {"isQueued", student.getQueuedState()}
    };

    return students[id].getToiletState();
}

void ToiletList::queueStudent(const int id) {
    Student student = students[id];

    // send the student to the toilet, if it's available
    if (checkToiletAvailability(student.getSubject())) {
        updateStudentToiletStatus(id, true);
    } else {
        // otherwise queue the student in his subjects queue
        toiletQueueMap[student.getSubject()].push(student);
        student.setQueuedState(true);
    }
}

void ToiletList::returnStudent(const int id) {
    const string subject = students[id].getSubject();
    updateStudentToiletStatus(id, false);

    if (!toiletQueueMap[subject].empty()) {

        // get the next student in line
        Student nextStudent = toiletQueueMap[subject].front();
        // send the student to the toilet
        updateStudentToiletStatus(nextStudent.getId(), true);
        // remove the student from the queue
        toiletQueueMap[subject].pop();
        // remove the student from the queue
        nextStudent.setQueuedState(false);
    }
}
