//
// Created by Oskar on 08.12.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include "main.h"
#include <QLineEdit>

using namespace std;

gui::gui(QWidget *parent)
    : QWidget(parent), buttonQueue("Queue", this), textFieldQueue(this),
    buttonReturn("Return", this), textFieldReturn(this),
    buttonSubjectStatus ("Subject Status", this), textFieldSubjectStatus(this),
    buttonStudentStatus ("Student Status", this), textFieldStudentStatus(this),
    labelLastOutput(this)
{

    ui->setupUi(this);
    // set size and location of the buttons
    buttonQueue.setGeometry(QRect(QPoint(100, 90), QSize(200, 50)));
    buttonReturn.setGeometry(QRect(QPoint(310, 90), QSize(200, 50)));
    buttonSubjectStatus.setGeometry(QRect(QPoint(520, 90), QSize(200, 50)));
    buttonStudentStatus.setGeometry(QRect(QPoint(730, 90), QSize(200, 50)));

    // Set size and location of the text fields
    textFieldQueue.setGeometry(QRect(QPoint(100, 50), QSize(200, 30)));
    textFieldReturn.setGeometry(QRect(QPoint(310, 50), QSize(200, 30)));
    textFieldSubjectStatus.setGeometry(QRect(QPoint(520, 50), QSize(200, 30)));
    textFieldStudentStatus.setGeometry(QRect(QPoint(730, 50), QSize(200, 30)));

    // set size and location of labels
    labelLastOutput.setGeometry(QRect(QPoint(000, 0), QSize(1000, 50)));
    labelLastOutput.setText("Last Output Label");
    labelLastOutput.setAlignment(Qt::AlignCenter);

    // Connect button signal to appropriate slot
    connect(&buttonQueue, &QPushButton::released, this, &gui::handleQueueButton);
    connect(&buttonReturn, &QPushButton::released, this, &gui::handleReturnButton);
    connect(&buttonSubjectStatus, &QPushButton::released, this, &gui::handleSubjectStatusButton);
    connect(&buttonStudentStatus, &QPushButton::released, this, &gui::handleStudentStatusButton);

    //buttonQueue.setStyleSheet("background-color: white; color: black;");
}

void gui::handleQueueButton() const {
    // Convert the result of toInt() to uint16_t
    const string name = textFieldQueue.text().toStdString();
    const uint16_t id = getStudentId(name);
    queueStudent(id);
}

void gui::handleReturnButton() const {
    // Convert the result of toInt() to uint16_t
    const string name = textFieldReturn.text().toStdString();
    const uint16_t id = getStudentId(name);
    returnStudent(id);
}

void gui::handleSubjectStatusButton() {
    const string subject = textFieldSubjectStatus.text().toStdString();
    updateLastOutputLabel(subjectStatus(subject));
}

void gui::handleStudentStatusButton() {
    const string name = textFieldStudentStatus.text().toStdString();
    const uint16_t id = getStudentId(name);
    updateLastOutputLabel(studentStatus(id));
}

void gui::updateLastOutputLabel(const QString& text) {
    labelLastOutput.setText(text);
}

gui::~gui() {
    delete ui;
}
