#pragma once
#include <QString>
#include "json.hpp"
#include <QList>

class CurseMetaDB {
public:
    CurseMetaDB();

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
        int primaryAuthor;
        QList<int> authors;
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
};
