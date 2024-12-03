//
// Created by Oskar on 03.12.2024.
//

#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;


class Student {
public:
    Student(int *pNextFreeId, const string &lastName, const string &firstName, const string &subject);
    int getId();
    string getLastName();
    string getFirstName();
    string getSubject();
    bool getToiletState();
    void setToiletState(bool state);
private:
    int id;
    string lastName;
    string firstName;
    string subject;
    bool isOnToilet;
};



#endif //STUDENT_H
