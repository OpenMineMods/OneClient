#pragma once

#include <QtWidgets>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow {
public:

    MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

    Ui_MainWindow _ui;
};