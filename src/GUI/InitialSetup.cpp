#include "InitialSetup.h"
#include "MainWindow.h"
#include "Utils.h"
#include "DownloadUtil.h"
#include "Minecraft/Yggdrasil.h"
#include "Minecraft/AuthSession.h"
#include "Minecraft/MojangInfo.h"

#include <QSettings>
#include <QByteArray>

using namespace MojangInfo;

InitialSetupWindow::InitialSetupWindow(QWidget *parent, Qt::WindowFlags flags) : QDialog(parent, flags) {
    _ui.setupUi(this);

    QString style = Utils::loadStyleSheet("main");
    this->setStyleSheet(style);

    conf_file = MainWindow::config_dir + "/oneclient.ini";
    QSettings settings(conf_file, QSettings::NativeFormat);

    if (!settings.value("analytics/uuid", false).toBool()) {
        settings.setValue("analytics/uuid", Utils::generateUUID());
    }

    _ui.tabWidget->setTabEnabled(3, false);
    QObject::connect(_ui.pushButton, &QPushButton::clicked, this, &InitialSetupWindow::nextTab);
    QObject::connect(_ui.pushButton_2, &QPushButton::clicked, this, &InitialSetupWindow::nextTab);
    connect(_ui.pushButton_3, &QPushButton::clicked, this, &InitialSetupWindow::nextTab);
}

void InitialSetupWindow::nextTab() {
    int ind = _ui.tabWidget->currentIndex();
    if (ind == 2) {
        AuthSession ses = Yggdrasil::login(_ui.login_username->text(), _ui.login_password->text());
        if (!ses.is_valid) {
            _ui.login_label->setText("Invalid Login!");
        }
        ses.writeToFile(MainWindow::data_dir + "/auth.dat");
        _ui.login_label->setText("Logged in as " + ses.profile.name);
        _ui.tabWidget->setTabEnabled(0, false);
        _ui.tabWidget->setTabEnabled(1, false);
        _ui.tabWidget->setTabEnabled(2, false);
        QSettings settings(conf_file, QSettings::NativeFormat);
        settings.setValue("setup_done", true);
        settings.setValue("analytics/enabled", _ui.analytics->isChecked());
        settings.setValue("autoupdate", _ui.autoupdate->isChecked());
        settings.setValue("java/min_ram", 512);
        settings.setValue("java/max_ram", 4096);
        _ui.prog_label->setText("Downloading Latest CurseMeta");
        DownloadUtil dlu;
        connect(&dlu, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
        dlu.downloadFile("https://openminemods.digitalfishfun.com/raw_cleaned.json.xz", MainWindow::cache_dir + "/meta.json.xz");
        system(("xz -d " + MainWindow::cache_dir + "/meta.json.xz").toStdString().c_str());
        _ui.prog_label->setText("Downloading Minecraft version manifest");
        dlu.downloadFile(VERSION_MANIFEST, MainWindow::cache_dir + "/minecraft.json");
        done(1);
        return;
    }
    _ui.tabWidget->setTabEnabled(ind + 1, true);
    _ui.tabWidget->setCurrentIndex(ind + 1);
}

void InitialSetupWindow::downloadProgress(qint64 bytesRecived, qint64 totalBytes) {
    _ui.prog_1->setMaximum(totalBytes);
    _ui.prog_1->setValue(bytesRecived);
}
