#include <iostream>
#include <vector>
#include <QApplication>
#include <windows.h>

#include "ToiletList.h"
#include "Student.h"
#include "FileLoader.h"
#include "gui.h"
#include "main.h"
#include "json.hpp"

void terminalInterface(ToiletList toiletList, const std::vector<std::string>& subjects);
void windowsWarnDialogue(const std::wstring& errorMessage);
std::vector<std::string> subjects;

ToiletList toiletList{};

int main(int argc, char *argv[]) {
    qDebug() << "Main started";
    std::vector<Student> students;

    if (argc < 2) {
        qDebug() << "No file path provided. Please enter the path to your file:";
        std::string path;
        std::cin >> path;
        students = FileLoader::loadFile(path);
    } else {
        students = FileLoader::loadFile(argv[1]);
    }

    subjects = FileLoader::getSubjects(students);

    toiletList.init(students, subjects);
    //terminalInterface(toiletList, subjects);

    qDebug() << "Toiletlist started";

    QApplication app(argc, argv);
    gui g;
    g.show();

    qDebug() << "GUI started";

    return QApplication::exec();
}

void terminalInterface(ToiletList& toiletList, const std::vector<std::string>& subjects) {
    std::cout << "Welcome!" << std::endl;
    while (true) {
        // welcome text
        std::cout << "Available commands:\nstatus, studentStatus, queue, return, stop" << std::endl;

        // get user input
        std::string input;
        std::cin >> input;

        // analyse input
        if (input == "status") {
            // output status of toilet for each subject
            for (const std::string& subject : subjects) {
                std::cout << toiletList.getToiletStatus(subject) << std::endl;
            }
        }
        else if (input == "studentStatus") {
            // get student id from user
            std::cout << "Enter student id: " << std::endl;
            int id;
            std::cin >> id;

            // output student status
            std::cout << toiletList.getStudentStatus(id) << std::endl;
        }
        else if (input == "queue") {
            // get student id from user
            std::cout << "Enter student id: " << std::endl;
            int id;
            std::cin >> id;

            // queue student
            toiletList.queueStudent(id);
            std::cout << "student " << id << " queued" << std::endl;
        }
        else if (input == "return") {
            // get student id from user
            std::cout << "Enter student id: " << std::endl;
            int id;
            std::cin >> id;

            // return student
            toiletList.returnStudent(id);
            std::cout << "student " << id << " returned" << std::endl;
        }
        else if (input == "stop") return;
        else {
            std::cout << "Invalid input." << std::endl;
        }
    }
}

// If the subjects toilet is available, the students gets directly sent to the toilet. Otherwise, the student gets added to the subjects queue
void queueStudent(const uint16_t& id) {
    try {
        toiletList.queueStudent(id);
    } catch (const std::invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student name");
    }
}

// returns a student from the toilet and sends the next one from the queue, if a next student from the queue exists
void returnStudent(const uint16_t& id) {
    try {
        toiletList.returnStudent(id);
    } catch (const std::invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student name");
    }
}

// returns the status of a subject in a single string
QString subjectStatus(const std::string& subject) {
    try {
        // return jsonToString(toiletList.getToiletStatus(subject));
        return QString::fromStdString(toiletList.getSubjectStatusString(subject));
    } catch (const std::invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid  Subject");
        return "";
    }
}

// returns the status of a student in a single string
QString studentStatus(const uint16_t& student) {
    try {
        // return jsonToString(toiletList.getStudentStatus(student));
        return QString::fromStdString(toiletList.getStudentStatusString(student));
    } catch (const std::invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student name");
        return "";
    }
}

// returns the ID of the given student
uint16_t getStudentId(const std::string& name) {
    try {
        return toiletList.getIdFromStudent(name);
    } catch (const std::invalid_argument& e) {
        qDebug() << e.what();
        return 65535;
    }
}

QString getStudentOnToilet(const std::string& subject) {
    Student* studentOnToilet = toiletList.getStudentOnToilet(subject);
    if (studentOnToilet == nullptr) {
        return "";
    }
    return QString::fromStdString(studentOnToilet->getName());
}

// creates a Windows error message
void windowsWarnDialogue(const std::wstring& errorMessage) {
    MessageBox(
        nullptr,
        errorMessage.c_str(),
        L"An error occurred!",
        MB_ICONERROR | MB_OK
    );
}

std::vector<std::string> getSubjects() {
    return subjects;
}

bool getSubjectAvailability(const std::string& subject) {
    return toiletList.checkToiletAvailability(subject);
}
