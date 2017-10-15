#include "MainWindow.h"
#include "utils.h"
#include <iostream>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);

    _config_dir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    _data_dir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    _cache_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
}
