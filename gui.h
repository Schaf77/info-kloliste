//
// Created by Oskar on 08.12.2024.
//

#ifndef GUI_H
#define GUI_H

#include <QLineEdit>
#include <QPushButton>


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
    QPushButton buttonQueue, buttonReturn;
    QLineEdit textFieldQueue, textFieldReturn;
private slots:
    void handleQueueButton();
    void handleReturnButton();
};


#endif //GUI_H
