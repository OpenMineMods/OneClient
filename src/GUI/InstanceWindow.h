#pragma once

#include <QtWidgets>
#include <QSettings>
#include <QMainWindow>
#include "ui_InstanceWindow.h"

class InstanceWindow : public QMainWindow {
    Q_OBJECT
public:
    InstanceWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
    Ui_InstanceWindow _ui;
};
