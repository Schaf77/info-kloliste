//
// Created by Oskar on 08.12.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include "main.h"
#include <QLineEdit>
#include <QPalette>

using namespace std;

gui::gui(QWidget *parent)
    : QWidget(parent),
      buttonQueue("Queue", this),
textFieldQueue(this),
      buttonReturn("Return", this),
      textFieldReturn(this),
      buttonSubjectStatus("Subject Status", this),
      textFieldSubjectStatus(this),
      buttonStudentStatus("Student Status", this),
      textFieldStudentStatus(this),
      labelLastOutput(this)
{
    ui->setupUi(this);

    // Create top layout for input fields and buttons
    auto *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(&textFieldQueue);
    inputLayout->addWidget(&textFieldReturn);
    inputLayout->addWidget(&textFieldSubjectStatus);
    inputLayout->addWidget(&textFieldStudentStatus);

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(&buttonQueue);
    buttonLayout->addWidget(&buttonReturn);
    buttonLayout->addWidget(&buttonSubjectStatus);
    buttonLayout->addWidget(&buttonStudentStatus);

    // Main layout
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(&labelLastOutput);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);

    createSubjectLabels(); // sets up subjectLayout
    mainLayout->addLayout(subjectLayout);

    // Connect signals
    connect(&buttonQueue, &QPushButton::released, this, &gui::handleQueueButton);
    connect(&buttonReturn, &QPushButton::released, this, &gui::handleReturnButton);
    connect(&buttonSubjectStatus, &QPushButton::released, this, &gui::handleSubjectStatusButton);
    connect(&buttonStudentStatus, &QPushButton::released, this, &gui::handleStudentStatusButton);
}


void gui::createSubjectLabels() {
    subjectLayout = new QVBoxLayout;

    QMap<QString, QString> subjects;
    subjects.insert("Math", "complete");
    subjects.insert("Science", "in progress");
    subjects.insert("History", "not started");

    for (auto it = subjects.cbegin(); it != subjects.cend(); ++it) {
        auto *label = new QLabel(it.key());
        label->setAlignment(Qt::AlignCenter);
        QPalette palette = label->palette();

        if (it.value() == "complete") {
            palette.setColor(QPalette::Window, Qt::green);
        } else if (it.value() == "in progress") {
            palette.setColor(QPalette::Window, Qt::yellow);
        } else {
            palette.setColor(QPalette::Window, Qt::red);
        }

        label->setPalette(palette);
        label->setAutoFillBackground(true);
        subjectLayout->addWidget(label);
        subjectLabels[it.key()] = label;
    }
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
    delete subjectLayout;
}
