//
// Created by Oskar on 08.12.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include "main.h"

#include <QLineEdit>
#include <QPalette>

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

    // set values for button and text field sizes
    constexpr uint8_t BUTTON_HEIGHT_MIN = 20, BUTTON_WIDTH_MIN = 20;
    constexpr uint8_t BUTTON_HEIGHT_MAX = 50, BUTTON_WIDTH_MAX = 200;
    constexpr uint8_t TEXT_FIELD_HEIGHT_MIN = 20, TEXT_FIELD_WIDTH_MIN = 20;
    constexpr uint8_t TEXT_FIELD_HEIGHT_MAX = 40, TEXT_FIELD_WIDTH_MAX = 200;

    // set button size limits
    QVector<QPushButton*> buttons;
    buttons.push_back(&buttonQueue);
    buttons.push_back(&buttonReturn);
    buttons.push_back(&buttonSubjectStatus);
    buttons.push_back(&buttonStudentStatus);

    for (QPushButton* pButton : buttons) {
        pButton->setMinimumSize(BUTTON_WIDTH_MIN, BUTTON_HEIGHT_MIN);
        pButton->setMaximumSize(BUTTON_WIDTH_MAX, BUTTON_HEIGHT_MAX);
        pButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // set text field size limits
    QVector<QLineEdit*> textFields;
    textFields.push_back(&textFieldQueue);
    textFields.push_back(&textFieldReturn);
    textFields.push_back(&textFieldSubjectStatus);
    textFields.push_back(&textFieldStudentStatus);

    for (QLineEdit* pTextField : textFields) {
        pTextField->setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
        pTextField->setMaximumSize(TEXT_FIELD_WIDTH_MAX, TEXT_FIELD_HEIGHT_MAX);
        pTextField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    // set label size and limits
    labelLastOutput.setMinimumSize(TEXT_FIELD_WIDTH_MIN, TEXT_FIELD_HEIGHT_MIN);
    labelLastOutput.setMaximumSize(1000, TEXT_FIELD_HEIGHT_MAX);
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

    createSubjectLabels(); // sets up subjectLabelLayout
    mainLayout->addLayout(subjectLayout);

    // Connect signals
    connect(&buttonQueue, &QPushButton::released, this, &gui::handleQueueButton);
    connect(&buttonReturn, &QPushButton::released, this, &gui::handleReturnButton);
    connect(&buttonSubjectStatus, &QPushButton::released, this, &gui::handleSubjectStatusButton);
    connect(&buttonStudentStatus, &QPushButton::released, this, &gui::handleStudentStatusButton);
}


void gui::createSubjectLabels() {
    // create the layout for the 2 layouts containing the students and the subjects names
    subjectLayout = new QVBoxLayout;

    // create the layout for the subjects labels and students
    subjectLabelLayout = new QHBoxLayout;
    subjectStudentLayout = new QHBoxLayout;

    // import subjects from file
    subjectsImport = getSubjects();

    // convert subject strings to QStrings and store them in a QVector<QString>
    QVector<QString> subjects;
    for (const std::string& subject : subjectsImport) {
        subjects.push_back(QString::fromStdString(subject));
    }

    // create a Label for each subject and student
    for (const QString& subject : subjects) {
        // create label for subject
        auto *subjectLabel = new QLabel(subject);
        subjectLabel->setAlignment(Qt::AlignCenter);
        QPalette palette = subjectLabel->palette();

        palette.setColor(QPalette::Window, Qt::green);

        subjectLabel->setPalette(palette);
        subjectLabel->setAutoFillBackground(true);
        subjectLabel->setStyleSheet("QLabel { font-size: 20px; color: black; }");
        subjectLabel->setMinimumSize(100, 50);
        subjectLabel->setMaximumSize(200, 90);
        subjectLabelLayout->addWidget(subjectLabel);
        subjectLabels[subject] = subjectLabel;

        // create label for student
        QString student = getStudentOnToilet(subject.toStdString());
        auto *studentLabel = new QLabel(student);
        studentLabel->setAlignment(Qt::AlignCenter);
        subjectStudentLayout->addWidget(studentLabel);

        subjectStudentLabels[subject] = studentLabel;

    }
    subjectLayout->addLayout(subjectLabelLayout);
    subjectLayout->addLayout(subjectStudentLayout);
}

void gui::updateSubjectLabels() {
    for (const std::string& subject : subjectsImport) {
        if (getSubjectAvailability(subject)) {
            // get subject label
            QLabel* label = subjectLabels[QString::fromStdString(subject)];

            // update label color
            QPalette palette = label->palette();
            palette.setColor(QPalette::Window, Qt::green);
            label->setPalette(palette);

            // redraw label
            label->update();

            // remove student from label
            QLabel * studentLabel = subjectStudentLabels[QString::fromStdString(subject)];
            studentLabel->setText("");
            studentLabel->update();
        } else {
            // get subject label
            QLabel* label = subjectLabels[QString::fromStdString(subject)];

            // update label color
            QPalette palette = label->palette();
            palette.setColor(QPalette::Window, Qt::red);
            label->setPalette(palette);

            // redraw label
            label->update();

            // get new student on toilet
            QString newStudent = getStudentOnToilet(subject);
            QLabel * studentLabel = subjectStudentLabels[QString::fromStdString(subject)];
            studentLabel->setText(newStudent);
            studentLabel->update();
        }
    }
}


void gui::handleQueueButton() {
    // Convert the result of toInt() to uint16_t
    const std::string name = textFieldQueue.text().toStdString();
    const uint16_t id = getStudentId(name);
    queueStudent(id);
    updateSubjectLabels();
}

void gui::handleReturnButton() {
    // Convert the result of toInt() to uint16_t
    const std::string name = textFieldReturn.text().toStdString();
    const uint16_t id = getStudentId(name);
    returnStudent(id);
    updateSubjectLabels();
}

void gui::handleSubjectStatusButton() {
    const std::string subject = textFieldSubjectStatus.text().toStdString();
    updateLastOutputLabel(subjectStatus(subject));
}

void gui::handleStudentStatusButton() {
    const std::string name = textFieldStudentStatus.text().toStdString();
    const uint16_t id = getStudentId(name);
    updateLastOutputLabel(studentStatus(id));
}

void gui::updateLastOutputLabel(const QString& text) {
    labelLastOutput.setText(text);
}

gui::~gui() {
    delete ui;
    delete subjectLabelLayout;
    delete subjectStudentLayout;
}
