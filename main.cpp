#include "GUI/MainWindow.h"
#include <QApplication>

QString MainWindow::data_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
QString MainWindow::config_dir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
QString MainWindow::cache_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

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
        qDebug() << MainWindow::config_dir;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
