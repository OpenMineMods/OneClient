#pragma once

#include <QString>
#include <QMap>
#include <QStringList>
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
    QVector<QString> orderedVersions;
    QString latest_release;
    QString latest_snapshot;
};

struct Rule {
    bool allow;
    QStringList allowed;
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
    bool native;
    QVector<Rule> rules;
};


struct AssetIndex {
    QString id;
    QString sha1;
    QString url;
    int totalsize;
    int size;
};

class MinecraftVersion {
public:
    MinecraftVersion();

    void loadFromFile(QString file);

    QVector<MinecraftFile> libraries;

    int total_size;
    AssetIndex asset_index;
    MinecraftDownload client;
    MinecraftDownload server;
    QString id;
    QString main_class;
    QString args;
    QString release_time;
    ReleaseType type;
};

struct MinecraftAsset {
    QString hash;
    int size;
};


class MinecraftAssets {
public:
    void loadFromFile(QString file);
    QMap<QString,MinecraftAsset> objects;
};

