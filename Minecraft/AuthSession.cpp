#include "AuthSession.h"

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
