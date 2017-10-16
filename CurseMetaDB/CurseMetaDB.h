#pragma once
#include <QString>
#include <QList>
#include <QJsonObject>

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
        QList<QString> authors;
        QString desc;
        QString page;
        QList<QString> versions;
        QList<int> files;
        QList<int> attachments;
    };

    struct CurseFile {
        int id;
        int date;
        QList<QString> versions;
        QList<int> deps;
        QString dl;
        QString filename;
        int project;
    };

    static CurseProject project_from_json(const QJsonObject& j);
    static CurseFile file_from_json(const QJsonObject& j);

private:
    QJsonObject raw_data;
};
