#pragma once

#include <QtWidgets>
#include <QSettings>
#include "ui_SetupDialog.h"

class InitialSetupWindow : public QDialog {
public:
    InitialSetupWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    void nextTab();

    Ui_SetupDialog _ui;
private:
    QString conf_file;
};
