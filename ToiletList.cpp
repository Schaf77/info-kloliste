//
// Created by Oskar on 03.12.2024.
//

#include <string>
#include <utility>
#include <algorithm>
#include <iostream>
#include <format>
#include "ToiletList.h"
#include "json.hpp"

using json = nlohmann::json;

ToiletList::ToiletList() = default;

void ToiletList::init(vector<Student> students, const vector<string> &subjects) {
    // transfer ownership of students and subjects vector
    this->students = move(students);
    this->subjects = move(subjects);

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

Student* ToiletList::getStudentOnToilet(const string& subject) {
    for (Student &student : this->students) {
        if (student.getToiletState() && student.getSubject() == subject) {
            return &student;
        }
    }
    return nullptr;
}


json ToiletList::getStudentStatus(const uint16_t& id) const {
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

json ToiletList::getToiletStatus(const string& subject) {
    if (ranges::find(subjects, subject) == subjects.end()) throw invalid_argument("Subject not found");

    json output = {
        {"subject", subject},
        {"availability", checkToiletAvailability(subject)},
        {"queueLength", toiletQueueMap[subject].size()}
    };

    return output;
}

string ToiletList::getStudentStatusString(const uint16_t& id) const {
    try {
        Student student = students.at(id);

        string output = format("Name: {}, Subject: {}, is queued: {}, is on toilet: {}",
            student.getName(),
            student.getSubject(),
            student.getQueuedState(),
            student.getToiletState());

        return output;
    } catch (out_of_range& e) {
        throw invalid_argument("Student not found");
    }
}

string ToiletList::getSubjectStatusString(const string& subject) {
    if (ranges::find(subjects, subject) == subjects.end()) throw invalid_argument("Subject not found");

    string output = format("Subject: {}. Availability: {}. Queue length: {}",
        subject,
        checkToiletAvailability(subject),
        toiletQueueMap[subject].size());

    return output;
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
        // set variables for increased readability
        Student* student = &students.at(id);
        const string subject = student->getSubject();

        // only proceed if student is on the toilet
        if (student->getToiletState() == false) return;

        // remove returned student from the toilet
        updateStudentToiletStatus(id, false);

        // only send the next student from the queue if the queue isn't empty
        if (!toiletQueueMap[subject].empty()) {
            // get the next student in line
            Student& pNextStudent = toiletQueueMap[subject].front();
            // send the student to the toilet
            updateStudentToiletStatus(pNextStudent.getId(), true);
            // remove the student from the queue
            updateStudentQueueStatus(pNextStudent.getId(), false);
            toiletQueueMap[subject].pop();
        }
    } catch (const out_of_range& e) {
        cerr << "Out of Range error: " << e.what() << endl;
        throw invalid_argument("Student not found");
    }
}
