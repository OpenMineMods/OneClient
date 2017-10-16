#include "Utils.h"
#include <regex>
#include <iostream>
#include <string>
#include <QWidget>
#include <QFileInfo>
#include <time.h>
#include <math.h>
#include <stdio.h>

QString Utils::loadStyleSheet(QString name) {
    QFile stylesheet(":/style/" + name + ".qss");
    stylesheet.open(QFile::ReadOnly);
    std::string s_stylesheet = QString(stylesheet.readAll()).toStdString();
    std::string orig_stylesheet = s_stylesheet;
    std::smatch m;
    std::regex var("(\\$.+):\\s*(.+);");
    std::regex alpha("\\$alpha\\((.*),\\s*(\\d+)\\)");
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
    s_stylesheet = orig_stylesheet;
    while (std::regex_search(s_stylesheet, m, alpha)) {
        std::string color_code(m[1]);
        std::string new_code("rgba(");
        new_code.append(std::to_string(std::stoi(color_code.substr(1, 2), 0, 16)));
        new_code.append(", ");
        new_code.append(std::to_string(std::stoi(color_code.substr(3, 2), 0, 16)));
        new_code.append(", ");
        new_code.append(std::to_string(std::stoi(color_code.substr(5, 2), 0, 16)));
        new_code.append(", ");
        new_code.append(m[2]);
        new_code.append(")");
        while (orig_stylesheet.find(m[0]) != std::string::npos) {
            orig_stylesheet.replace(orig_stylesheet.find(m[0]), m[0].length(), new_code);
        }
        s_stylesheet = m.suffix().str();
    }
    return QString::fromStdString(orig_stylesheet);
}

QString Utils::generateUUID() {
    srand(time(NULL));
    char buffer[64];
    sprintf(buffer, "%x%x-%x%x-%x%x-%x%x",
            rand(), rand(), rand(), rand(),
            rand(), rand(), rand(), rand());
    return QString(buffer);
}

void Utils::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

bool Utils::fileExists(QString path) {
    QFileInfo check_file(path);
    return check_file.exists() && check_file.isFile();
}

static const char* scale[] = {
    "",
    "K",
    "M",
    "B"
};

QString Utils::formatNumber(double n, int decimals) {
    int digits = n==0? 0 : 1+floor(log10l(fabs(n)));
    // determine base 10 exponential
    int exp = digits <= 4? 0 : 3*((digits-1)/3);
    // normalized number
    double m = n / powl(10, exp);
    // no decimals? then don't print any
    if ( m - static_cast<long>(n) == 0 )
        decimals = 0;
    static const char* fmt[] = {"%1 %2 %3", "%1 %2 %3"};
    QString s = QString::number(m,'f',decimals).append(scale[exp/3]);
//    QString s = QString(fmt[exp>0]).arg(decimals).arg(m).arg(QChar(*scale[exp/3]));
    return s;
}
