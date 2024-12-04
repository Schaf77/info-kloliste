#include <iostream>
#include <vector>
#include <list>
#include "ToiletList.h"
#include "Student.h"
#include "FileLoader.h"

using namespace std;

int main() {
    FileLoader loader;
    // loader.loadFile("C:\\Users\\Oskar\\CLionProjects\\info-kloliste\\test.txt");
    list<string> testSubjects = {"Maths", "English", "German"};

    ToiletList toiletList(loader.loadExample(), testSubjects);
    cout << "English: " << toiletList.checkToiletAvailability("English") << endl;
    cout << "Maths: " << toiletList.checkToiletAvailability("Maths") << endl;
    cout << "German: " << toiletList.checkToiletAvailability("German") << endl;
    toiletList.queueStudent(0);
    cout << "Changed" << endl;
    cout << "English: " << toiletList.checkToiletAvailability("English") << endl;
    cout << "Maths: " << toiletList.checkToiletAvailability("Maths") << endl;
    cout << "German: " << toiletList.checkToiletAvailability("German") << endl;
    toiletList.queueStudent(3);
    cout << "Changed" << endl;
    cout << "English: " << toiletList.checkToiletAvailability("English") << endl;
    cout << "Maths: " << toiletList.checkToiletAvailability("Maths") << endl;
    cout << "German: " << toiletList.checkToiletAvailability("German") << endl;
    toiletList.returnStudent(0);
    return 0;
}
