#include "CurseMetaDB.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

CurseMetaDB::CurseMetaDB() {

}

void CurseMetaDB::load(QByteArray meta) {
    raw_data = QJsonDocument::fromJson(meta).object();
    QJsonObject projects = raw_data.value("projects").toObject();
    for (int projectIndex = 0; projectIndex < projects.size(); ++projectIndex) {
        CurseProject prj = CurseMetaDB::project_from_json(projects[projects.keys().at(projectIndex)].toObject());
        qDebug() << prj.id;
    }
}

CurseMetaDB::CurseProject CurseMetaDB::project_from_json(const QJsonObject &j) {
    CurseProject* project = new CurseMetaDB::CurseProject();

    project->id = j["id"].toInt();

    if (j["type"].toString() == "mod") project->type = ProjectType::MOD;
    if (j["type"].toString() == "modpack") project->type == ProjectType::MODPACK;
    if (j["type"].toString() == "texturepack") project->type == ProjectType::TEXTUREPACK;
    if (j["type"].toString() == "world") project->type == ProjectType::WORLD;

    project->title = j["title"].toString();
    //project->authors = j["authors"];
    project->desc = j["desc"].toString();
    project->page = j["site"].toString();
    //project->versions = j["versions"];
    //project->files = j["files"];
    //project->attachments = j["attachments"];

    return *project;
}
