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

    bool is_valid;
    QString access_token;
    QString client_token;
    User profile;
};
