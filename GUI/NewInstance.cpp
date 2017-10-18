#include "NewInstance.h"
#include "MainWindow.h"
#include "Utils.h"

NewInstance::NewInstance(QWidget *parent) : QDialog(parent) {
    _ui.setupUi(this);
    setStyleSheet(Utils::loadStyleSheet("main"));

    QVectorIterator<QString> iter(MainWindow::vers.orderedVersions);
    while (iter.hasNext()) {
        _ui.mc_ver->addItem(iter.next());
    }
}
