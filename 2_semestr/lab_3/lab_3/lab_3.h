#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab_3.h"

class lab_3 : public QMainWindow
{
    Q_OBJECT

public:
    lab_3(QWidget *parent = nullptr);
    ~lab_3();

private:
    Ui::lab_3Class ui;
};

