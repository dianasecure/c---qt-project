#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOPA89.h"

class OOPA89 : public QMainWindow
{
    Q_OBJECT

public:
    OOPA89(QWidget *parent = nullptr);
    ~OOPA89();


private:
    Ui::OOPA89Class ui;
};
