#pragma once

#include <QtWidgets>
#include <QString>
#include <QObject>
#include <QSettings>

class MinecraftInstance : public QObject
{
    Q_OBJECT
public:
    MinecraftInstance(QString baseDir, QObject *parent = NULL);

    void setVersion(QString minecraft, QString forge);
    QPair<QString, QString> getVersion();

    QString getIcon() const;
    QString getName() const;

public slots:
    void launch();
    void outputChanged();

private:
    void setupInstance();

    QString m_baseDir;
    QString m_mcDir;
    QProcess *process;
};
