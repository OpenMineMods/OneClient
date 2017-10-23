#include "CurseMetaDB.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringListIterator>
#include <QDebug>
#include <string>
#include <Fuzz/fuzzywuzzy.hpp>
#include <algorithm>

CurseMetaDB::CurseMetaDB() {

}

void CurseMetaDB::load(QByteArray meta) {
    QJsonObject raw_data = QJsonDocument::fromJson(meta).object();
    QJsonObject raw_projects = raw_data.value("projects").toObject();
    QJsonObject raw_files = raw_data.value("files").toObject();
    QStringListIterator iter(raw_projects.keys());
    CurseProject project;
    while (iter.hasNext()) {
        project = CurseMetaDB::project_from_json(raw_projects[iter.next()].toObject());
        projects.insert(project.id, project);
    }
    QStringListIterator iter2(raw_files.keys());
    CurseFile file;
    while (iter2.hasNext()) {
        file = CurseMetaDB::file_from_json(raw_files[iter2.next()].toObject());
        files.insert(file.id, file);
    }
    qDebug() << "Loaded" << projects.size() << "projects and" << files.size() << "files.";
}

void CurseMetaDB::clearRam() {
    projects.clear();
    files.clear();
}

QVector<CurseMetaDB::CurseProject> CurseMetaDB::search(const QString query, const ProjectType projectType, const int limit) {
    QVector<CurseProject> results;
    QVector<QPair<CurseProject, int>> candidates;
    QListIterator<CurseProject> iter(projects.values());
    CurseProject project;
    int title_partial;
    int title_full;
    while (iter.hasNext()) {
        project = iter.next();
        if (project.type != projectType) continue;
        if (query == "*") {
            results.append(project);
            continue;
        }
        title_partial = fuzz::partial_ratio(query.toStdString(), project.title.toStdString());
        title_full = fuzz::ratio(query.toStdString(), project.title.toStdString());
        candidates.append(QPair<CurseProject, int>(project, title_partial + title_full));
    }
    if (query == "*") {
        std::sort(results.begin(), results.end(), CurseMetaDB::compare_projects);
        results.erase(results.begin() + limit, results.end());
    } else {
        std::sort(candidates.begin(), candidates.end(), CurseMetaDB::compareCloseness);
        for(int i = 0; i < limit; i++){
            results.append(candidates[i].first);
        }
    }
    return results;
}

bool CurseMetaDB::compare_projects(const CurseProject &p1, const CurseProject &p2) {
    return p1.popularity > p2.popularity;
}

bool CurseMetaDB::compareCloseness(const QPair<CurseProject, int> p1, const QPair<CurseProject, int> p2) {
    return p1.second > p2.second;
}

CurseMetaDB::CurseProject CurseMetaDB::project_from_json(const QJsonObject &j) {
    CurseProject project;

    project.id = j["id"].toInt();

    if (j["type"].toString() == "mod") project.type = ProjectType::MOD;
    else if (j["type"].toString() == "modpack") project.type = ProjectType::MODPACK;
    else if (j["type"].toString() == "texturepack") project.type = ProjectType::TEXTUREPACK;
    else project.type = ProjectType::WORLD;

    project.title = j["title"].toString();
    project.authors = j["authors"].toArray();
    project.desc = j["desc"].toString();
    project.page = j["site"].toString();
    project.versions = j["versions"].toArray();
    project.files = j["files"].toArray();
    project.attachments = j["attachments"].toArray();
    project.popularity = j["popularity"].toDouble();
    project.downloads = j["downloads"].toInt();

    if (project.attachments.size() > 0) {
        for (int i = 0; i < project.attachments.size(); i++) {
            if (project.attachments[i].toObject()["default"].toBool()) {
                project.icon_url = project.attachments[i].toObject()["url"].toString();
                QStringList url_parts = project.icon_url.split(".");
                project.icon_name = QString::number(project.id) + "." + url_parts[url_parts.length() - 1];
            }
        }
    } else {
        project.icon_url = "";
        project.icon_name = "";
    }

    return project;
}

CurseMetaDB::CurseFile CurseMetaDB::file_from_json(const QJsonObject &j) {
    CurseFile file;

    file.id = j["id"].toInt();
    file.date = j["date"].toInt();
    file.versions = j["versions"].toArray();
    file.deps = j["dependencies"].toArray();
    file.dl = j["url"].toString();
    file.filename = j["filename"].toString();
    file.project = j["project"].toInt();

    return file;
}
