#include "InitialSetup.h"
#include "MainWindow.h"
#include "utils.h"

#include <QSettings>

InitialSetupWindow::InitialSetupWindow(QWidget *parent, Qt::WindowFlags flags) : QDialog(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);

    conf_file = MainWindow::config_dir + "/oneclient.ini";
    QSettings settings(conf_file, QSettings::NativeFormat);

    _ui.tabWidget->setTabEnabled(1, false);
    _ui.tabWidget->setTabEnabled(2, false);
    QObject::connect(_ui.pushButton, &QPushButton::clicked, this, &InitialSetupWindow::nextTab);
    QObject::connect(_ui.pushButton_2, &QPushButton::clicked, this, &InitialSetupWindow::nextTab);
}

void InitialSetupWindow::nextTab() {
    int ind = _ui.tabWidget->currentIndex();
    if (ind == 1) {
        _ui.tabWidget->setTabEnabled(0, false);
        _ui.tabWidget->setTabEnabled(1, false);
        QSettings settings(conf_file, QSettings::NativeFormat);
        settings.setValue("setup_done", true);
        this->done(1);
        return;
    }
    _ui.tabWidget->setTabEnabled(ind + 1, true);
    _ui.tabWidget->setCurrentIndex(ind + 1);
}
