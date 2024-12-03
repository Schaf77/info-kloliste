//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include <list>

#include "ToiletList.h"


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

bool ToiletList::getStudentStatus(const int id) {
    return students[id].getToiletState();
}

void ToiletList::queueStudent(const int id) {
    Student student = students[id];
    if (checkToiletAvailability(student.getSubject())) {
        updateStudentToiletStatus(id, true);
    } else {
        toiletQueueMap[student.getSubject()].push(student);
    }
}

void ToiletList::returnStudent(const int id) {
    string subject = students[id].getSubject();
    updateStudentToiletStatus(id, false);

    if (!toiletQueueMap[subject].empty()) {
        // gets the next student from the subject's queue where a student just came back, send him to the toilet and remove him from the queue
        Student nextStudent = toiletQueueMap[subject].front();
        updateStudentToiletStatus(nextStudent.getId(), true);
        toiletQueueMap[subject].pop();
    }
}
