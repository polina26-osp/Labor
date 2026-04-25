#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab_4.h"

class lab_4 : public QMainWindow
{
    Q_OBJECT

public:
    lab_4(QWidget *parent = nullptr);
    ~lab_4();

private:
    Ui::lab_4Class ui;
};

