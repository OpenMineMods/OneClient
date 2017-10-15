#include "MainWindow.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    _ui.analytics_check->setChecked(true);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);
}
