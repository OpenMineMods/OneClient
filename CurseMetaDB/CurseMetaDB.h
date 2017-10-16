#pragma once
#include <QString>
#include "json.hpp"
#include <QList>

using json = nlohmann::json;

class CurseMetaDB {
public:
    CurseMetaDB(QString meta);

    enum ProjectType {
        MOD,
        MODPACK,
        TEXTUREPACK,
        WORLD
    };

    struct CurseProject {
        int id;
        ProjectType type;
        std::string title;
        std::string primaryAuthor;
        QList<QString> authors;
        std::string desc;
        std::string page;
        QList<QString> versions;
        QList<int> files;
        QList<int> attachments;
    };

    struct CurseFile {
        int id;
        int date;
        QList<QString> versions;
        QList<int> deps;
        std::string dl;
        std::string filename;
        int project;
    };

    CurseProject project_from_json(const json& j);
    CurseFile file_from_json(const json& j);

private:
    json raw_data;
};
