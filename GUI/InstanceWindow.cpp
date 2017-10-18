#include "InstanceWindow.h"
#include "Utils.h"
#include <QMainWindow>

InstanceWindow::InstanceWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent,flags) {
    _ui.setupUi(this);
    this->setStyleSheet(Utils::loadStyleSheet("main"));
}
