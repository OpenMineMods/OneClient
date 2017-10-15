#include "GUI/MainWindow.h"
#include <QApplication>

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
    parser.process(a);

    MainWindow w;
    w.show();

    return a.exec();
}
