#include "GUI/MainWindow.h"
#include "Minecraft/MinecraftVersions.h"
#include "Minecraft/AuthSession.h"
#include "Utils.h"
#include <QApplication>
#include <QDir>

QString MainWindow::data_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/oneclient";
QString MainWindow::config_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/oneclient";
QString MainWindow::cache_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/oneclient";
MinecraftVersions MainWindow::vers = MinecraftVersions();
AuthSession MainWindow::ses = AuthSession();
CurseMetaDB MainWindow::db = CurseMetaDB();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("OpenMineMods");
    QCoreApplication::setOrganizationDomain("openminemods.digitalfishfun.com");
    QCoreApplication::setApplicationName("OneClient++");

    QCommandLineParser parser;
    parser.setApplicationDescription("OneClient++");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addVersionOption();

    QCommandLineOption targetDirectoryOption(QStringList() << "t" << "target-directory",
                                             "Directory to use for storage",
                                             "directory");
    parser.addOption(targetDirectoryOption);

    parser.process(a);

    if (parser.isSet(targetDirectoryOption)) {
        QString targetDir = parser.value(targetDirectoryOption);
        QDir().mkpath(targetDir);
        MainWindow::data_dir = targetDir + "/data";
        MainWindow::config_dir = targetDir + "/config";
        MainWindow::cache_dir = targetDir + "/cache";
    } else {
        QString port_dir = QApplication::applicationDirPath() + "/data";
        QDir port_qdir(port_dir);
        if (port_qdir.exists()) {
            MainWindow::data_dir = port_dir + "/data";
            MainWindow::config_dir = port_dir + "/config";
            MainWindow::cache_dir = port_dir + "/cache";
        }
    }

    QDir().mkpath(MainWindow::data_dir);
    QDir().mkpath(MainWindow::data_dir + "/instances");
    QDir().mkpath(MainWindow::config_dir);
    QDir().mkpath(MainWindow::cache_dir);
    QDir().mkpath(MainWindow::cache_dir + "/icons");
    QDir().mkpath(MainWindow::cache_dir + "/manifests");
    QDir().mkpath(MainWindow::cache_dir + "/assets/indexes");
    QDir().mkpath(MainWindow::cache_dir + "/assets/objects");

    qDebug() << "Running on" << OS_NAME;

    MainWindow w;
    w.show();

    return a.exec();
}
