//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include "ToiletList.h"
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

ToiletList::ToiletList() = default;

void ToiletList::init(vector<Student> students, const vector<string> &subjects) {
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

void ToiletList::updateStudentToiletStatus(const uint16_t id, const bool isOnToilet) {
    students.at(id).setToiletState(isOnToilet);
}

void ToiletList::updateStudentQueueStatus(const uint16_t id, bool isQueued) {
    students.at(id).setQueuedState(isQueued);
}

uint16_t ToiletList::getIdFromStudent(const string& name) {
    for (Student student : this->students) {
        if (student.getName() == name) {
            return student.getId();
        }
    }
    throw std::invalid_argument("Student not found");
}


json ToiletList::getStudentStatus(const uint16_t id) const {
    try {
        Student student = students.at(id);

        json output = {
            {"name", student.getName()},
            {"subject", student.getSubject()},
            {"isQueued", student.getQueuedState()},
            {"isOnToilet", student.getToiletState()}
        };

        return output;
    } catch (out_of_range& e) {
        throw invalid_argument("Student not found");
    }
}

json ToiletList::getToiletStatus(string subject) {
    try {
        json output = {
            {"subject", subject},
            {"availability", checkToiletAvailability(subject)},
            {"queueLength", toiletQueueMap[subject].size()}
        };

        return output;
    } catch (exception &e) {
        throw invalid_argument("Invalid subject");
    }
}


void ToiletList::queueStudent(const uint16_t id) {
    try {
        // fetch the student and catch the out_of_bounds error, if the id parameter is wrong
        Student *pStudent = &(students.at(id));
        const string subject = pStudent->getSubject();

        // check if student is already queued or on the toilet
        if (pStudent->getQueuedState() || pStudent->getToiletState()) return;

        // send the student to the toilet, if it's available
        if (checkToiletAvailability(subject)) {
            updateStudentToiletStatus(id, true);
        } else {
            // otherwise queue the student in his subject's queue
            toiletQueueMap[subject].push(*pStudent);
            pStudent->setQueuedState(true);
        }
    } catch (const out_of_range& oor) {
        cerr << "Out of Range error: " << oor.what() << endl;
        throw invalid_argument("Student not found");
    }
}


void ToiletList::returnStudent(const uint16_t id) {
    try {
        // set variable for increased readability
        const string subject = students.at(id).getSubject();

        // remove returned student from the toilet
        updateStudentToiletStatus(id, false);

        // only send the next student from the queue if the queue isn't empty
        if (!toiletQueueMap[subject].empty()) {

            // get the next student in line
            Student *pNextStudent = &toiletQueueMap[subject].front();
            // send the student to the toilet
            updateStudentToiletStatus(pNextStudent->getId(), true);
            // remove the student from the queue
            updateStudentQueueStatus(pNextStudent->getId(), false);
            toiletQueueMap[subject].pop();
        }
    } catch (const out_of_range& e) {
        cerr << "Out of Range error: " << e.what() << endl;
        throw invalid_argument("Student not found");
    }
}
