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

using namespace std;

void terminalInterface(ToiletList toiletList, const vector<string>& subjects);
void windowsWarnDialogue(const wstring& errorMessage);
vector<string> subjects;

ToiletList toiletList{};

int main(int argc, char *argv[]) {
    qDebug() << "Main started";
    vector<Student> students;

    if (argc < 2) {
        qDebug() << "No file path provided. Using default .\\kloliste.csv";
        students = FileLoader::loadFile("kloliste.csv");
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

void terminalInterface(ToiletList toiletList, const vector<string>& subjects) {
    cout << "Welcome!" << endl;
    while (true) {
        // welcome text
        cout << "Available commands:\nstatus, studentStatus, queue, return, stop" << endl;

        // get user input
        string input;
        cin >> input;

        // analyse input
        if (input == "status") {
            // output status of toilet for each subject
            for (const string& subject : subjects) {
                cout << toiletList.getToiletStatus(subject) << endl;
            }
        }
        else if (input == "studentStatus") {
            // get student id from user
            cout << "Enter student id: " << endl;
            int id;
            cin >> id;

            // output student status
            cout << toiletList.getStudentStatus(id) << endl;
        }
        else if (input == "queue") {
            // get student id from user
            cout << "Enter student id: " << endl;
            int id;
            cin >> id;

            // queue student
            toiletList.queueStudent(id);
            cout << "student " << id << " queued" << endl;
        }
        else if (input == "return") {
            // get student id from user
            cout << "Enter student id: " << endl;
            int id;
            cin >> id;

            // return student
            toiletList.returnStudent(id);
            cout << "student " << id << " returned" << endl;
        }
        else if (input == "stop") return;
        else {
            cout << "Invalid input." << endl;
        }
    }
}


// functions for gui
void queueStudent(const uint16_t& id) {
    try {
        toiletList.queueStudent(id);
    } catch (const invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student ID");
    }
}

void returnStudent(const uint16_t& id) {
    try {
        toiletList.returnStudent(id);
    } catch (const invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student ID");
    }
}

QString subjectStatus(const std::string& subject) {
    try {
        // return jsonToString(toiletList.getToiletStatus(subject));
        return QString::fromStdString(toiletList.getSubjectStatusString(subject));
    } catch (const invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid  Subject");
        return "";
    }
}

QString studentStatus(const uint16_t& student) {
    try {
        // return jsonToString(toiletList.getStudentStatus(student));
        return QString::fromStdString(toiletList.getStudentStatusString(student));
    } catch (const invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student ID");
        return "";
    }
}

uint16_t getStudentId(const std::string& name) {
    try {
        return toiletList.getIdFromStudent(name);
    } catch (const invalid_argument& e) {
        qDebug() << e.what();
        windowsWarnDialogue(L"Invalid Student name");
        return 65535;
    }
}

QString jsonToString(const json& jsonObj) {
    return QString::fromStdString(jsonObj.dump());
}

vector<QString> jsonStudentStatusToString(const nlohmann::json &jsonObj) {
    // convert json to vector
    vector<QString> studentStatus;
    studentStatus.push_back(QString::fromStdString(jsonObj.at("name")));
    studentStatus.push_back(QString::fromStdString(jsonObj.at("subject")));
    studentStatus.push_back(QString::fromStdString(jsonObj.at("isQueued")));
    studentStatus.push_back(QString::fromStdString(jsonObj.at("isOnToilet")));

    return studentStatus;
}

vector<QString> jsonSubjectStatusToString(const nlohmann::json &jsonObj) {
    // convert json to vector
    vector<QString> subjectStatus;
    subjectStatus.push_back(QString::fromStdString(jsonObj.at("subject")));
    subjectStatus.push_back(QString::fromStdString(jsonObj.at("availability")));
    subjectStatus.push_back(QString::fromStdString(jsonObj.at("queueLength")));

    return subjectStatus;
}

void windowsWarnDialogue(const wstring& errorMessage) {
    MessageBox(
        nullptr,
        errorMessage.c_str(),
        L"An error occurred!",
        MB_ICONERROR | MB_OK
    );
}

vector<string> getSubjects() {
    return subjects;
}

bool getSubjectAvailability(const string& subject) {
    return toiletList.checkToiletAvailability(subject);
}
