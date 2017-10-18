#pragma once

#include <QString>
#include <QMap>
#include <QVector>

enum ReleaseType {
    RELEASE,
    SNAPSHOT
};

struct BasicMinecraftVersion {
    QString id;
    ReleaseType type;
    QString release_time;
    QString url;
};

class MinecraftVersions {
public:
    MinecraftVersions();

    void loadFromFile(QString file);

    QMap<QString, BasicMinecraftVersion> versions;
    QString latest_release;
    QString latest_snapshot;
};

struct MinecraftDownload {
    int size;
    QString sha1;
    QString path;
    QString url;
};

struct MinecraftFile {
    QString name;
    MinecraftDownload download;
};

class MinecraftVersion {
public:
    MinecraftVersion();

    void loadFromFile(QString file);

    QVector<MinecraftFile> libraries;

    int total_size;
    QString asset_index;
    MinecraftDownload client;
    MinecraftDownload server;
    QString id;
    QString main_class;
    QString args;
    QString release_time;
    ReleaseType type;
};
