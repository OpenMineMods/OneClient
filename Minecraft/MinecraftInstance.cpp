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
        if(!libraries.isEmpty()) libraries = libraries % ":" % path;
        else libraries = path;
        if (f.native) {
            QString extract_path = MainWindow::data_dir % "/natives/" % m_ver.id;
            QDir().mkpath(extract_path);
            system(("unzip " + path + " -n -qq -d " + extract_path).toStdString().c_str());
        }
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

    // Clear RAM up
    // TODO: Reload after instance exists
    MainWindow::db.clearRam();

    // TODO: Detect java
    QString run = "/usr/lib/jvm/java-8-openjdk/bin/java";

    QString natives_dir = MainWindow::data_dir % "/natives/" % m_ver.id;

    // Natives, needs to be the first argument
    arguments << "-Djava.library.path=" % natives_dir;
    // For debugging purposes
    arguments << "-XshowSettings:properties";
    // ClassPath, contains <minecraft jar>:<library jars seperated by ":"> entry point
    arguments << "-cp" << jar_loc % ":" % libraries << m_ver.main_class;
    // Information about the user
    arguments << "--username" << MainWindow::ses.profile.name;
    arguments << "--uuid" << MainWindow::ses.profile.id;
    arguments << "--accessToken" << MainWindow::ses.access_token;
    arguments << "--userType" << (MainWindow::ses.profile.legacy ? "legacy" : "mojang");
    // Information about the game
    arguments << "--version" << m_ver.id;
    arguments << "--gameDir" << m_mcDir;
    arguments << "--assetsDir" << MainWindow::cache_dir % "/assets/";
    arguments << "--assetsIndex" << m_ver.asset_index.id;
    // Branding
    arguments.append("--versionType OneClient++");

    qDebug() << "Launching Instance " << getName();
    process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, this, &MinecraftInstance::outputChanged);
    connect(process, &QProcess::readyReadStandardError, this, &MinecraftInstance::outputChanged);
    process->start(run, arguments);
}

void MinecraftInstance::outputChanged() {
    qDebug() << process->readAllStandardOutput();
    qDebug() << process->readAllStandardError();
}
