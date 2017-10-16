#pragma once
#include <QString>
#include <QList>
#include <QMap>
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
        double popularity;
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

    QList<CurseProject> search(const QString query, const ProjectType projectType, const int limit = 0);

    static CurseProject project_from_json(const QJsonObject &j);
    static CurseFile file_from_json(const QJsonObject &j);

    static bool compare_projects(const CurseProject &p1, const CurseProject &p2);

private:
    QMap<int, CurseProject> projects;
    QMap<int, CurseFile> files;
};
