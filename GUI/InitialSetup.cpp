#include "InitialSetup.h"
#include "utils.h"

InitialSetup::InitialSetup(QWidget *parent, Qt::WindowFlags flags) : QDialog(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);
}
