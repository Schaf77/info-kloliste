//
// Created by Oskar on 08.12.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"

#include <iostream>

#include "ui_gui.h"


gui::gui(QWidget *parent)
    : QWidget(parent), m_button("My Button", this)
{

    ui->setupUi(this);
    // set size and location of the button
    m_button.setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(&m_button, &QPushButton::released, this, &gui::handleButton);

    m_button.setStyleSheet("background-color: white; color: black;");
}

void gui::handleButton()
{
    qDebug() << "Button clicked.";

    startToiletList();
}

gui::~gui() {
    delete ui;
}
