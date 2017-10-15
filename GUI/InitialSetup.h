#pragma once

#include <QtWidgets>
#include "ui_SetupDialog.h"

class InitialSetup : public QDialog {
public:
    InitialSetup(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    Ui_SetupDialog _ui;
};
