#pragma once
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>

class CurseMetaDB {
public:
    CurseMetaDB();
    void load(QByteArray meta);

    enum ProjectType {
        MOD,
        MODPACK,
        TEXTUREPACK,
        WORLD
    };

    struct CurseProject {
        int id;
        ProjectType type;
        QString title;
        QString primaryAuthor;
        QJsonArray authors;
        QString desc;
        QString page;
        QJsonArray versions;
        QJsonArray files;
        QJsonArray attachments;
    };

    struct CurseFile {
        int id;
        int date;
        QJsonArray versions;
        QJsonArray deps;
        QString dl;
        QString filename;
        int project;
    };

    static CurseProject* project_from_json(const QJsonObject &j);
    static CurseFile* file_from_json(const QJsonObject &j);

private:
    QList<CurseProject> projects;
    QList<CurseFile> files;
};
