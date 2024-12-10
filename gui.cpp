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

    // button min
    constexpr uint8_t BUTTON_HEIGHT_MIN = 20;
    constexpr uint8_t BUTTON_WIDTH_MIN = 20;

    // text field min
    constexpr uint8_t TEXT_FIELD_HEIGHT_MIN = 20;
    constexpr uint8_t TEXT_FIELD_WIDTH_MIN = 20;

    // button max
    constexpr uint8_t BUTTON_HEIGHT_MAX = 50;
    constexpr uint8_t BUTTON_WIDTH_MAX = 200;

    // text field max
    constexpr uint8_t TEXT_FIELD_HEIGHT_MAX = 40;
    constexpr uint8_t TEXT_FIELD_WIDTH_MAX = 200;

    // set button size limits
    buttonQueue.setMinimumSize(BUTTON_WIDTH_MIN, BUTTON_HEIGHT_MIN);
    buttonQueue.setMaximumSize(BUTTON_WIDTH_MAX, BUTTON_HEIGHT_MAX);
    buttonQueue.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    buttonReturn.setMinimumSize(BUTTON_WIDTH_MIN, BUTTON_HEIGHT_MIN);
    buttonReturn.setMaximumSize(BUTTON_WIDTH_MAX, BUTTON_HEIGHT_MAX);
    buttonReturn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    buttonSubjectStatus.setMinimumSize(BUTTON_WIDTH_MIN, BUTTON_HEIGHT_MIN);
    buttonSubjectStatus.setMaximumSize(BUTTON_WIDTH_MAX, BUTTON_HEIGHT_MAX);
    buttonSubjectStatus.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    buttonStudentStatus.setMinimumSize(BUTTON_WIDTH_MIN, BUTTON_HEIGHT_MIN);
    buttonStudentStatus.setMaximumSize(BUTTON_WIDTH_MAX, BUTTON_HEIGHT_MAX);
    buttonStudentStatus.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // set text field size limits
    textFieldQueue.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    textFieldQueue.setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
    textFieldQueue.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    textFieldReturn.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    textFieldReturn.setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
    textFieldReturn.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    textFieldSubjectStatus.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    textFieldSubjectStatus.setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
    textFieldSubjectStatus.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    textFieldStudentStatus.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    textFieldStudentStatus.setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
    textFieldStudentStatus.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // set label size and limits
    labelLastOutput.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    labelLastOutput.setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
    labelLastOutput.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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
    subjectLayout = new QHBoxLayout;

    subjectsImport = getSubjects();

    QVector<QString> subjects;
    for (const string& subject : subjectsImport) {
        subjects.push_back(QString::fromStdString(subject));
    }

    for (const QString& subject : subjects) {
        auto *label = new QLabel(subject);
        label->setAlignment(Qt::AlignCenter);
        QPalette palette = label->palette();

        palette.setColor(QPalette::Window, Qt::green);

        label->setPalette(palette);
        label->setAutoFillBackground(true);
        label->setStyleSheet("QLabel { font-size: 20px; color: black; }");
        label->setMinimumSize(100, 50);
        label->setMaximumSize(200, 90);
        subjectLayout->addWidget(label);
        subjectLabels[subject] = label;
    }
}

void gui::updateSubjectLabels() {
    for (const string& subject : subjectsImport) {
        if (getSubjectAvailability(subject)) {
            // get subject label
            QLabel* label = subjectLabels[QString::fromStdString(subject)];

            // update label color
            QPalette palette = label->palette();
            palette.setColor(QPalette::Window, Qt::green);
            label->setPalette(palette);

            // redraw label
            label->update();
        } else {
            // get subject label
            QLabel* label = subjectLabels[QString::fromStdString(subject)];

            // update label color
            QPalette palette = label->palette();
            palette.setColor(QPalette::Window, Qt::red);
            label->setPalette(palette);

            // redraw label
            label->update();
        }
    }
}


void gui::handleQueueButton() {
    // Convert the result of toInt() to uint16_t
    const string name = textFieldQueue.text().toStdString();
    const uint16_t id = getStudentId(name);
    queueStudent(id);
    updateSubjectLabels();
}

void gui::handleReturnButton() {
    // Convert the result of toInt() to uint16_t
    const string name = textFieldReturn.text().toStdString();
    const uint16_t id = getStudentId(name);
    returnStudent(id);
    updateSubjectLabels();
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
