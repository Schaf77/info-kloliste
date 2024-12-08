//
// Created by Oskar on 08.12.2024.
//

#ifndef GUI_H
#define GUI_H

#include <QLineEdit>
#include <QPushButton>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget {
Q_OBJECT

public:
    explicit gui(QWidget *parent = nullptr);
    ~gui() override;
private:
    Ui::gui *ui{};
    QPushButton buttonQueue, buttonReturn, buttonSubjectStatus, buttonStudentStatus;
    QLineEdit textFieldQueue, textFieldReturn, textFieldSubjectStatus, textFieldStudentStatus;
    QLabel labelLastOutput;
private slots:
    void handleQueueButton() const;
    void handleReturnButton() const;
    void handleSubjectStatusButton();
    void handleStudentStatusButton();
    void updateLastOutputLabel(const QString &text);
};


#endif //GUI_H
