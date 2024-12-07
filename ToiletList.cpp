//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include "ToiletList.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

ToiletList::ToiletList(vector<Student> students, const vector<string>& subjects) {
    // transfer ownership of students vector
    this->students = move(students);

    // create a queue for each subject
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
    students.at(id).setToiletState(isOnToilet);
}

json ToiletList::getStudentStatus(const int id) const {
    Student student = students.at(id);

    json output = {
        {"name", student.getName()},
        {"subject", student.getSubject()},
        {"isQueued", student.getQueuedState()}
    };

    return output;
}

json ToiletList::getToiletStatus(string subject) {
    json output = {
        {"subject", subject},
        {"availability", checkToiletAvailability(subject)},
        {"queueLength", toiletQueueMap[subject].size()}
    };

    return output;
}


void ToiletList::queueStudent(const int id) {
    try {
        // fetch the student and catch the out_of_bounds error, if the id parameter is wrong
        Student student = students.at(id);

        // check if student is already queued or on the toilet
        if (student.getQueuedState() && student.getToiletState()) return;

        // send the student to the toilet, if it's available
        if (checkToiletAvailability(student.getSubject())) {
            updateStudentToiletStatus(id, true);
        } else {
            // otherwise queue the student in his subject's queue
            toiletQueueMap[student.getSubject()].push(student);
            student.setQueuedState(true);
        }
    } catch (const out_of_range& oor) {
        cerr << "Out of Range error: " << oor.what() << endl;
    }
}


void ToiletList::returnStudent(const int id) {
    // set variables for increased readability
    const string subject = students.at(id).getSubject();
    updateStudentToiletStatus(id, false);

    // only send the next student from the queue if the queue isn't empty
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
