#include <iostream>
#include <vector>
#include <list>
#include "ToiletList.h"
#include "Student.h"
#include "FileLoader.h"

using namespace std;

int main() {
    FileLoader loader;
    //TODO relative Path
    vector<Student> students = loader.loadFile("C:\\Users\\Oskar\\CLionProjects\\info-kloliste\\kloliste-beispiel.csv");
    vector<string> subjects = loader.getSubjects(students);

    ToiletList toiletList(students, subjects);
    cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    toiletList.queueStudent(0);
    cout << "Changed" << endl;
    cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    toiletList.queueStudent(1);
    cout << "Changed" << endl;
    cout << "MA L1: " << toiletList.checkToiletAvailability("MA L1") << endl;
    cout << "GE G1: " << toiletList.checkToiletAvailability("GE G1") << endl;
    cout << "SP G1: " << toiletList.checkToiletAvailability("SP G1") << endl;
    toiletList.returnStudent(0);
    return 0;
}
