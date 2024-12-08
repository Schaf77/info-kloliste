//
// Created by Oskar on 08.12.2024.
//

#ifndef GUI_H
#define GUI_H

#include <QPushButton>
#include "main.h"


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
    QPushButton m_button;
private slots:
    void handleButton();
};


#endif //GUI_H
