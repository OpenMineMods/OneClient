#include "DownloadUtil.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QFile>
#include <QDir>

void DownloadUtil::downloadFile(const QString &url, const QString &dest) {
    QNetworkAccessManager m_netMan;
    QNetworkReply *reply = m_netMan.get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QFile file(dest);
    file.open(QIODevice::WriteOnly);
    file.write(reply->readAll());
    delete reply;
}
