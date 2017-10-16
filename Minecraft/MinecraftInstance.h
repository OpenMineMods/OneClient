#pragma once

#include <QtWidgets>
#include <QString>
#include <QSettings>

class MinecraftInstance
{
public:
    MinecraftInstance(QString baseDir);

    void setVersion(QString minecraft, QString forge);

    QString getIcon() const;
    QString getName() const;

private:
    void setupInstance();

    QString m_baseDir;
    QString m_mcDir;
};
