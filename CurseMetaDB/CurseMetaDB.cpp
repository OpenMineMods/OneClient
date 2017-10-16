#include "CurseMetaDB.h"

CurseMetaDB::CurseMetaDB(QString meta) {
    //raw_data = json::parse(meta.toStdString().c_str());
}

CurseMetaDB::CurseProject CurseMetaDB::project_from_json(const json &j) {
    CurseProject* project = new CurseMetaDB::CurseProject();

    project->id = j["id"];

    if (j["type"] == "mod") project->type = ProjectType::MOD;
    if (j["type"] == "modpack") project->type == ProjectType::MODPACK;
    if (j["type"] == "texturepack") project->type == ProjectType::TEXTUREPACK;
    if (j["type"] == "world") project->type == ProjectType::WORLD;

    project->title = j["title"];
    //project->authors = j["authors"];
    project->desc = j["desc"];
    project->page = j["site"];
    //project->versions = j["versions"];
    //project->files = j["files"];
    //project->attachments = j["attachments"];

    return *project;
}
