#include "MinecraftVersions.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include "Utils.h"
#include <QJsonArray>
#include <QMap>
#include <QVariantMap>

MinecraftVersions::MinecraftVersions() {

}

void MinecraftVersions::loadFromFile(QString file) {
    QFile versionsFile(file);
    versionsFile.open(QIODevice::ReadOnly);
    QJsonObject versionsObject = QJsonDocument::fromJson(versionsFile.readAll()).object();
    versionsFile.close();

    QJsonObject latest = versionsObject["latest"].toObject();
    latest_release = latest["release"].toString();
    latest_snapshot = latest["snapshot"].toString();

    QJsonArray c_versions = latest.value("versions").toArray();
    QJsonObject current;
    for (int i = 0; i < c_versions.size(); ++i) {
        BasicMinecraftVersion ver;
        current = c_versions[i].toObject();
        ver.id = current["id"].toString();
        if (current["type"].toString() == "release") ver.type = ReleaseType::RELEASE;
        else ver.type = ReleaseType::SNAPSHOT;
        ver.release_time = current["releaseTime"].toString();
        ver.url = current["url"].toString();
        versions.insert(ver.id, ver);
    }
}

MinecraftVersion::MinecraftVersion() {

}

void MinecraftVersion::loadFromFile(QString file) {
    QFile versionFile(file);
    versionFile.open(QIODevice::ReadOnly);
    QJsonObject versionObject = QJsonDocument::fromJson(versionFile.readAll()).object();
    versionFile.close();

    QJsonObject downloads = versionObject["downloads"].toObject();
    QJsonObject j_client = downloads["client"].toObject();
    QJsonObject j_server = downloads["server"].toObject();

    client.sha1 = j_client["sha1"].toString();
    client.size = j_client["size"].toInt();
    total_size += client.size;
    client.url = j_client["url"].toString();

    server.sha1 = j_server["sha1"].toString();
    server.size = j_server["size"].toInt();
    server.url = j_server["url"].toString();

    id = versionObject["id"].toString();
    QJsonObject indexObject = versionObject["assetIndex"].toObject();
    asset_index = AssetIndex();
    asset_index.id = indexObject["id"].toString();
    asset_index.sha1 = indexObject["sha1"].toString();
    asset_index.url = indexObject["url"].toString();
    asset_index.totalsize = indexObject["totalsize"].toInt();
    asset_index.size = indexObject["size"].toInt();
    main_class = versionObject["mainClass"].toString();
    args = versionObject["minecraftArguments"].toString();
    release_time = versionObject["releaseTime"].toString();

    if (versionObject["type"] == "release") type = ReleaseType::RELEASE;
    else type = ReleaseType::SNAPSHOT;

    QJsonArray libs = versionObject["libraries"].toArray();
    QJsonObject clib;
    for (int i = 0; i < libs.size(); ++i) {
        clib = libs[i].toObject();

        MinecraftFile file;
        file.name = clib["name"].toString();

        MinecraftDownload dl;

        if (clib.contains("natives")) {
            if (!clib["natives"].toObject().contains(OS_NAME)) continue;
            QString key = clib["natives"].toObject()[OS_NAME].toString();
            downloads = clib["downloads"].toObject()["classifiers"].toObject()[key].toObject();
        } else {
            downloads = clib["downloads"].toObject()["artifact"].toObject();
        }

        dl.size = downloads["size"].toInt();
        total_size += dl.size;
        dl.sha1 = downloads["sha1"].toString();
        dl.url = downloads["url"].toString();
        dl.path = downloads["path"].toString();

        file.download = dl;

        libraries.append(file);
    }
}

void MinecraftAssets::loadFromFile(QString file) {
    QFile assetsFile(file);
    assetsFile.open(QIODevice::ReadOnly);
    QJsonObject assetsObjects = QJsonDocument::fromJson(assetsFile.readAll()).object();
    assetsFile.close();

    QVariantMap assets = assetsObjects.toVariantMap();

}
