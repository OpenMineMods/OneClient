#include "MinecraftInstance.h"
#include "Utils.h"
#include "GUI/MainWindow.h"
#include "DownloadUtil.h"
#include "BackgroundDownloader.h"
#include "MinecraftVersions.h"
#include <QSettings>
#include <QStringListIterator>
#include <QStringList>

using namespace std;

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
        BasicMinecraftVersion ver = MainWindow::vers.versions[getVersion().first];
        dl.downloadFile(ver.url, mcver);
    }

    MinecraftVersion m_ver;
    m_ver.loadFromFile(mcver);

    QVectorIterator<MinecraftFile> iter(m_ver.libraries);
    MinecraftFile f;
    QString libraries;
    while (iter.hasNext()) {
        f = iter.next();
        QString path(MainWindow::data_dir + "/libraries/" + f.download.path);
        if (!Utils::fileExists(path)) {
            QDir().mkpath(MainWindow::data_dir + "/libraries/" + f.download.path.section("/", 0, -2));
            dl.downloadFile(f.download.url,path);
        }
        //Apparently the : needs to be ; on windows or something
        if(!libraries.isEmpty())
            libraries = libraries % ":" % path;
        else
            libraries = path;
    }

    QString mcassets = MainWindow::cache_dir + "/assets/indexes/" + getVersion().first + ".json";
    if (!Utils::fileExists(mcassets)) {
        dl.downloadFile(m_ver.asset_index.url, mcassets);
    }

    MinecraftAssets m_assets;
    m_assets.loadFromFile(mcassets);

    BackgroundDownloader bgdl;
    QStringListIterator mapIter(m_assets.objects.keys());
    while(mapIter.hasNext()) {
        QString key(mapIter.next());
        QString file = MainWindow::cache_dir + "/assets/objects/" + key;
        if(!Utils::fileExists(file)) {
            QDir dir = QFileInfo(file).absoluteDir();
            if(!dir.exists())
                dir.mkpath(dir.absolutePath());
            bgdl.setTarget("http://resources.download.minecraft.net/"+ file, file);
            bgdl.run();
            qDebug() << "Getting Asset: " << file;
        } else {
            //TODO hash check the file
        }
    }

    QString path(MainWindow::data_dir + "/libraries/" + f.download.path);

    QString jar_loc = MainWindow::data_dir + "/versions/" + m_ver.id + "/" + m_ver.id + ".jar";
    if (!Utils::fileExists(jar_loc)) {
        QDir().mkpath(jar_loc.section("/", 0, -2));
        dl.downloadFile(m_ver.client.url, jar_loc);
    }
    QStringList arguments;

//    arguments.append("");
    arguments.append("-Djava.library.path="%libraries);
    arguments.append(m_ver.main_class);
    arguments.append("--username " % MainWindow::ses.profile.name);
    arguments.append("--version " % m_ver.id);
    arguments.append("--gameDir " % m_mcDir);
    arguments.append("--assetsDir " % MainWindow::cache_dir + "/assets/");
    arguments.append("--assetIndex" %  m_ver.asset_index.id);
    arguments.append("--uuid " %  MainWindow::ses.profile.id);
    arguments.append("--accessToken " % MainWindow::ses.access_token);

    if (MainWindow::ses.profile.legacy)
        arguments.append("--userType legacy");
    else
        arguments.append("--userType mojang");
    arguments.append("--versionType OneClient++");

    qDebug() << "Launching Instance " << getName();
    QProcess *process = new QProcess(this);
    QString run = "/usr/lib/jvm/java-8-oracle/bin/java";
    qDebug() << arguments;
    process->startDetached(run,arguments);
}
