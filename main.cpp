#include <iostream>
#include <vector>
#include <QApplication>
#include "ToiletList.h"
#include "Student.h"
#include "FileLoader.h"
#include "gui.h"
#include "main.h"

using namespace std;

void terminalInterface(ToiletList toiletList, const vector<string>& subjects);

ToiletList toiletList{};

int main(int argc, char *argv[]) {
    qDebug() << "Main started";

    const vector<Student> students = FileLoader::loadFile(R"(C:\Users\Oskar\CLionProjects\info-kloliste\kloliste-beispiel.csv)");
    const vector<string> subjects = FileLoader::getSubjects(students);

    toiletList.init(students, subjects);
    //terminalInterface(toiletList, subjects);

    qDebug() << "Toiletlist started";

    QApplication app(argc, argv);
    gui g;
    g.show();

    qDebug() << "GUI started";

    return app.exec();
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

void queueStudent(const int& id) {
    qDebug() << "Queue started";
    toiletList.queueStudent(id);
    cout << toiletList.getStudentStatus(id) << endl;
}

void returnStudent(const int& id) {
    qDebug() << "Return started";
    toiletList.returnStudent(id);
    cout << toiletList.getStudentStatus(id) << endl;
}
