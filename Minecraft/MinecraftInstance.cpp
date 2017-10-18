#include "MinecraftInstance.h"
#include "Utils.h"
#include "GUI/MainWindow.h"
#include "DownloadUtil.h"
#include "BackgroundDownloader.h"
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

    QString mcassets = MainWindow::cache_dir + "/assets/indexes/" + getVersion().first + ".json";
    if (!Utils::fileExists(mcassets)) {
        dl.downloadFile(m_ver.asset_index.url, mcassets);
    }


    MinecraftAssets m_assets;
    BackgroundDownloader bgdl;

    QString jar_loc = MainWindow::data_dir + "/versions/" + m_ver.id + "/" + m_ver.id + ".jar";
    if (!Utils::fileExists(jar_loc)) {
        QDir().mkpath(jar_loc.section("/", 0, -2));
        dl.downloadFile(m_ver.client.url, jar_loc);
    }

    QString args(m_ver.args);

    args = args.replace("${auth_player_name}", MainWindow::ses.profile.name);
    args = args.replace("${version_name}", m_ver.id);
    args = args.replace("${game_directory}", m_mcDir);
    args = args.replace("${assets_root}", MainWindow::cache_dir + "/assets/");
    args = args.replace("${assets_index_name}", m_ver.asset_index.id);
    args = args.replace("${auth_uuid}", MainWindow::ses.profile.id);
    args = args.replace("${auth_access_token}", MainWindow::ses.access_token);
    if (MainWindow::ses.profile.legacy) args = args.replace("${user_type}", "legacy");
    else args = args.replace("${user_type}", "mojang");
    args = args.replace("${version_type}", "OneClient++");

    qDebug() << args;
    qDebug() << "Launching Instance " << getName();
}
