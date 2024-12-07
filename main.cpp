#include <iostream>
#include <vector>
#include "ToiletList.h"
#include "Student.h"
#include "FileLoader.h"

using namespace std;

void terminalInterface(ToiletList toiletList, const vector<string>& subjects);

int main() {
    //TODO relative Path
    const vector<Student> students = FileLoader::loadFile(R"(C:\Users\Oskar\CLionProjects\info-kloliste\kloliste-beispiel.csv)");
    const vector<string> subjects = FileLoader::getSubjects(students);

    ToiletList toiletList(students, subjects);
    terminalInterface(toiletList, subjects);
    // cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    // cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    // cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    // toiletList.queueStudent(0);
    // cout << "Changed" << endl;
    // cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    // cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    // cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    // toiletList.queueStudent(1);
    // cout << "Changed" << endl;
    // cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    // cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    // cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    // toiletList.returnStudent(0);


    return 0;
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


