#include "AuthSession.h"
#include <QFile>
#include <QJsonDocument>

AuthSession::AuthSession() {

}

AuthSession::AuthSession(QJsonObject resp) {
    if (resp.contains("error")) {
        is_valid = false;
        return;
    }
    is_valid = true;
    access_token = resp["accessToken"].toString();
    client_token = resp["clientToken"].toString();
    QJsonObject sel_prof = resp["selectedProfile"].toObject();
    profile.id = sel_prof["id"].toString();
    profile.name = sel_prof["name"].toString();
    profile.legacy = sel_prof["legacy"].toBool();
}

void AuthSession::loadFromFile(QString auth_f) {
    QFile authFile(auth_f);
    authFile.open(QIODevice::ReadOnly);
    QJsonObject authObject = QJsonDocument::fromBinaryData(authFile.readAll()).object();
    authFile.close();
    is_valid = authObject["valid"].toBool();
    access_token = authObject["token"].toString();
    client_token = authObject["client"].toString();
    profile.id = authObject["id"].toString();
    profile.name = authObject["name"].toString();
    profile.legacy = authObject["legay"].toBool();
}

void AuthSession::writeToFile(QString file) {
    QJsonObject out;
    out["valid"] = is_valid;
    out["token"] = access_token;
    out["client"] = client_token;
    out["id"] = profile.id;
    out["name"] = profile.name;
    out["legacy"] = profile.legacy;

    QFile authFile(file);
    authFile.open(QIODevice::WriteOnly);
    QJsonDocument outDoc(out);
    authFile.write(outDoc.toBinaryData());
}
