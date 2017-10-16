#include "GUI/MainWindow.h"
#include <QApplication>
#include <QDir>

QString MainWindow::data_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
QString MainWindow::config_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
QString MainWindow::cache_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
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

    QDir().mkdir(MainWindow::data_dir);
    QDir().mkdir(MainWindow::config_dir);
    QDir().mkdir(MainWindow::cache_dir);

    MainWindow w;
    w.show();

    return a.exec();
}
