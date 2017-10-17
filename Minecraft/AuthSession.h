#pragma once

#include <QString>
#include <QJsonObject>

struct User
{
    QString id;
    QString name;
    bool legacy;
};

class AuthSession
{
public:
    AuthSession(QJsonObject resp);
    AuthSession();

    void writeToFile(QString file);
    void loadFromFile(QString authFile);

    bool is_valid;
    QString access_token;
    QString client_token;
    User profile;
};
