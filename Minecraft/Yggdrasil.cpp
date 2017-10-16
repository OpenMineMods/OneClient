#include "Yggdrasil.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

AuthSession Yggdrasil::login(const QString &username, const QString &password) {
    QJsonObject auth_request;
    QJsonObject agent;
    agent["name"] = "Minecraft";
    agent["version"] = 1;
    auth_request["agent"] = agent;
    auth_request["username"] = username;
    auth_request["password"] = password;
    QNetworkAccessManager m_netMan;
    QJsonDocument doc(auth_request);
    QNetworkRequest req(QUrl(Auth_Constants::AUTH_ENDPOINT));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    qDebug() << doc.toJson();
    QNetworkReply *reply = m_netMan.post(req, doc.toJson());
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    qDebug() << reply->readAll();
}
