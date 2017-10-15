#include "MainWindow.h"
#include "InitialSetup.h"
#include "utils.h"
#include <iostream>
#include <sys/stat.h>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);

    QSettings settings(config_dir + "/oneclient.ini", QSettings::NativeFormat);

    if (!settings.value("setup_done", false).toBool()) {
        qDebug() << "Showing Initial Setup";
        InitialSetupWindow w;
        qDebug() << w.exec();
    }
}
