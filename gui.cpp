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
    : QWidget(parent), buttonQueue("Queue", this), textFieldQueue(this), buttonReturn("Return", this), textFieldReturn(this)
{

    ui->setupUi(this);
    // set size and location of the buttons
    buttonQueue.setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    buttonReturn.setGeometry(QRect(QPoint(310, 100), QSize(200, 50)));

    // Set size and location of the text field
    textFieldQueue.setGeometry(QRect(QPoint(100, 50), QSize(200, 30)));
    textFieldReturn.setGeometry(QRect(QPoint(310, 50), QSize(200, 30)));

    // Connect button signal to appropriate slot
    connect(&buttonQueue, &QPushButton::released, this, &gui::handleQueueButton);
    connect(&buttonReturn, &QPushButton::released, this, &gui::handleReturnButton);

    //buttonQueue.setStyleSheet("background-color: white; color: black;");
}

void gui::handleQueueButton()
{
    queueStudent(textFieldQueue.text().toInt());
}

void gui::handleReturnButton() {
    returnStudent(textFieldReturn.text().toInt());
}

gui::~gui() {
    delete ui;
}
