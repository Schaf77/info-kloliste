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
    buttonSudentStatus ("Student Status", this), textFieldSudentStatus(this),
    labelLastOutput(this)
{

    ui->setupUi(this);
    // set size and location of the buttons
    buttonQueue.setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    buttonReturn.setGeometry(QRect(QPoint(310, 100), QSize(200, 50)));
    buttonSubjectStatus.setGeometry(QRect(QPoint(520, 100), QSize(200, 50)));
    buttonSudentStatus.setGeometry(QRect(QPoint(730, 100), QSize(200, 50)));

    // Set size and location of the text fields
    textFieldQueue.setGeometry(QRect(QPoint(100, 50), QSize(200, 30)));
    textFieldReturn.setGeometry(QRect(QPoint(310, 50), QSize(200, 30)));
    textFieldSubjectStatus.setGeometry(QRect(QPoint(520, 50), QSize(200, 30)));
    textFieldSudentStatus.setGeometry(QRect(QPoint(730, 50), QSize(200, 30)));

    // set size and location of labels
    labelLastOutput.setGeometry(QRect(QPoint(000, 0), QSize(1000, 50)));
    labelLastOutput.setText("Last Output Label");
    labelLastOutput.setAlignment(Qt::AlignCenter);

    // Connect button signal to appropriate slot
    connect(&buttonQueue, &QPushButton::released, this, &gui::handleQueueButton);
    connect(&buttonReturn, &QPushButton::released, this, &gui::handleReturnButton);
    connect(&buttonSubjectStatus, &QPushButton::released, this, &gui::handleSubjectStatusButton);
    connect(&buttonSudentStatus, &QPushButton::released, this, &gui::handleStudentStatusButton);

    //buttonQueue.setStyleSheet("background-color: white; color: black;");
}

void gui::handleQueueButton() {
    // Convert the result of toInt() to uint16_t
    const uint16_t value = static_cast<uint16_t>(textFieldQueue.text().toInt());
    queueStudent(value);
}

void gui::handleReturnButton() {
    // Convert the result of toInt() to uint16_t
    const uint16_t value = static_cast<uint16_t>(textFieldReturn.text().toInt());
    returnStudent(value);
}

void gui::handleSubjectStatusButton() {
    const string subject = textFieldSubjectStatus.text().toStdString();
    updateLastCoutLabel(subjectStatus(subject));
}

void gui::handleStudentStatusButton() {
    const uint16_t student = static_cast<uint16_t>(textFieldSudentStatus.text().toInt());
    updateLastCoutLabel(studentStatus(student));
}

void gui::updateLastCoutLabel(const QString& text) {
    labelLastOutput.setText(text);
}

gui::~gui() {
    delete ui;
}
