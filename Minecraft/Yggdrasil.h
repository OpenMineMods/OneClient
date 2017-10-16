#pragma once

#include <QString>
#include <QtWidgets>
#include <QJsonObject>
#include "AuthSession.h"

namespace Auth_Constants {
const QString AUTH_ENDPOINT("https://authserver.mojang.com/authenticate");

const QString REAUTH_ENDPOINT("https://authserver.mojang.com/refresh");
}

class Yggdrasil
{
public:
    static AuthSession login(const QString& username, const QString& password);
};
