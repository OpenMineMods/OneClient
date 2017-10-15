#include "utils.h"
#include <regex>
#include <string>

Utils::Utils()
{

}

QString Utils::loadStyleSheet(QString name) {
    QFile stylesheet(":/style/main.qss");
    stylesheet.open(QFile::ReadOnly);
    std::string s_stylesheet = QString(stylesheet.readAll()).toStdString();
    std::string orig_stylesheet = s_stylesheet;
    std::smatch m;
    std::regex var("(\\$.+):\\s*(.+);");
    std::map<std::string, std::string> vars;
    while (std::regex_search(s_stylesheet, m, var)) {
        while (orig_stylesheet.find(m[0]) != std::string::npos) {
            orig_stylesheet.replace(orig_stylesheet.find(m[0]), m[0].length(), "");
        }
        while (orig_stylesheet.find(m[1]) != std::string::npos) {
            orig_stylesheet.replace(orig_stylesheet.find(m[1]), m[1].length(), m[2]);
        }
        s_stylesheet = m.suffix().str();
    }
    return QString::fromStdString(orig_stylesheet);
}
