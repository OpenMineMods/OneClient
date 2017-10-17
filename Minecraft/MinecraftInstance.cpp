#include "MinecraftInstance.h"
#include "Utils.h"
#include "GUI/MainWindow.h"
#include "DownloadUtil.h"
#include "MinecraftVersions.h"
#include <QSettings>

MinecraftInstance::MinecraftInstance(QString baseDir, QObject* parent) : QObject(parent) {
    m_baseDir = baseDir;
    m_mcDir = baseDir + "/minecraft";

    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);

    if (settings.value("instance/time_created", -1) < 0) {
        setupInstance();
    }
}

void MinecraftInstance::setupInstance() {
    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);

    settings.setValue("instance/name", m_baseDir.section('/', -1));
    settings.setValue("instance/time_created", QDateTime::currentMSecsSinceEpoch());
    settings.setValue("instance/playtime", 0);
    settings.setValue("instance/last_launch", 0);
    settings.setValue("instance/icon", "default");

    settings.setValue("minecraft/version", "1.7.10");
    settings.setValue("minecraft/forge", "10.13.4.1614");

    settings.setValue("modpack/id", -1);
    QDir().mkpath(m_mcDir);
}

void MinecraftInstance::setVersion(QString minecraft, QString forge) {
    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);

    settings.setValue("minecraft/version", minecraft);
    settings.setValue("minecraft/forge", forge);
}

QPair<QString, QString> MinecraftInstance::getVersion() {
    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);

    return QPair<QString, QString>(settings.value("minecraft/version").toString(), settings.value("forge/version").toString());
}

QString MinecraftInstance::getIcon() const {
    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);
    return settings.value("instance/icon", "default.svg").toString();
}

QString MinecraftInstance::getName() const {
    QSettings settings(m_baseDir + "/instance.ini", QSettings::NativeFormat);
    return settings.value("instance/name", "Unnamed Instance").toString();
}

void MinecraftInstance::launch() {
    QString mcver = MainWindow::cache_dir + "/manifests/" + getVersion().first + ".json";
    DownloadUtil dl;
    if (!Utils::fileExists(mcver)) {
        BasicMinecraftVersion ver = MainWindow::vers.versions[mcver];
        dl.downloadFile(ver.url, mcver);
    }
    MinecraftVersion m_ver;
    m_ver.loadFromFile(mcver);

    QVectorIterator<MinecraftFile> iter(m_ver.libraries);
    MinecraftFile f;
    while (iter.hasNext()) {
        f = iter.next();
        if (!Utils::fileExists(MainWindow::data_dir + "/libraries/" + f.download.path)) {
            QDir().mkpath(MainWindow::data_dir + "/libraries/" + f.download.path.section("/", 0, -2));
            dl.downloadFile(f.download.url, MainWindow::data_dir + "/libraries/" + f.download.path);
        }
    }

    qDebug() << "Launching Instance " << getName();
}
