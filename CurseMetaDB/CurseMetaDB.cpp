#include "CurseMetaDB.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringListIterator>
#include <QDebug>

CurseMetaDB::CurseMetaDB() {

}

void CurseMetaDB::load(QByteArray meta) {
    QJsonObject raw_data = QJsonDocument::fromJson(meta).object();
    QJsonObject raw_projects = raw_data.value("projects").toObject();
    QJsonObject raw_files = raw_data.value("files").toObject();
    QStringListIterator iter(raw_projects.keys());
    while (iter.hasNext()) {
        projects.append(*CurseMetaDB::project_from_json(raw_projects[iter.next()].toObject()));
    }
    QStringListIterator iter2(raw_files.keys());
    while (iter2.hasNext()) {
        files.append(*CurseMetaDB::file_from_json(raw_files[iter2.next()].toObject()));
    }
    qDebug() << "Loaded" << projects.size() << "projects and" << files.size() << "files.";
}

CurseMetaDB::CurseProject* CurseMetaDB::project_from_json(const QJsonObject &j) {
    CurseProject* project = new CurseMetaDB::CurseProject();

    project->id = j["id"].toInt();

    if (j["type"].toString() == "mod") project->type = ProjectType::MOD;
    else if (j["type"].toString() == "modpack") project->type = ProjectType::MODPACK;
    else if (j["type"].toString() == "texturepack") project->type = ProjectType::TEXTUREPACK;
    else project->type = ProjectType::WORLD;

    project->title = j["title"].toString();
    project->authors = j["authors"].toArray();
    project->desc = j["desc"].toString();
    project->page = j["site"].toString();
    project->versions = j["versions"].toArray();
    project->files = j["files"].toArray();
    project->attachments = j["attachments"].toArray();

    return project;
}

CurseMetaDB::CurseFile* CurseMetaDB::file_from_json(const QJsonObject &j) {
    CurseFile* file = new CurseMetaDB::CurseFile();

    file->id = j["id"].toInt();
    file->date = j["date"].toInt();
    file->versions = j["versions"].toArray();
    file->deps = j["dependencies"].toArray();
    file->dl = j["url"].toString();
    file->filename = j["filename"].toString();
    file->project = j["project"].toInt();

    return file;
}
