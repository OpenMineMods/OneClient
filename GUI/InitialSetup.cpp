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

    if (!settings.value("analytics/uuid", false).toBool()) {
        settings.setValue("analytics/uuid", Utils::generateUUID());
    }

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
        settings.setValue("analytics/enabled", _ui.analytics->isChecked());
        settings.setValue("autoupdate", _ui.autoupdate->isChecked());
        return;
    }
    _ui.tabWidget->setTabEnabled(ind + 1, true);
    _ui.tabWidget->setCurrentIndex(ind + 1);
}
