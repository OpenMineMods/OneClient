#-------------------------------------------------
#
# Project created by QtCreator 2017-10-15T10:58:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OneClientPP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        GUI/MainWindow.cpp \
        GUI/InitialSetup.cpp \
        DownloadUtil.cpp \
        CurseMetaDB/CurseMetaDB.cpp \
        GUI/PackWidget.cpp \
        BackgroundDownloader.cpp \
        Fuzz/fuzzywuzzy.cpp \
        Fuzz/utils.cpp \
        Fuzz/levenshtein.c \
        Fuzz/string_matcher.cpp \
        Fuzz/wrapper.cpp \
        Utils.cpp \
    Minecraft/MinecraftInstance.cpp \
    GUI/FlowLayout.cpp \
    GUI/InstanceWidget.cpp \
    Minecraft/Yggdrasil.cpp \
    Minecraft/AuthSession.cpp \
    GUI/LoginDialog.cpp

HEADERS += \
        GUI/MainWindow.h \
        GUI/InitialSetup.h \
        DownloadUtil.h \
        CurseMetaDB/CurseMetaDB.h \
        GUI/PackWidget.h \
        BackgroundDownloader.h \
        Fuzz/fuzzywuzzy.hpp \
        Fuzz/utils.hpp \
        Fuzz/common.hpp \
        Fuzz/levenshtein.h \
        Fuzz/string_matcher.hpp \
        Fuzz/wrapper.hpp \
        Utils.h \
        Minecraft/MinecraftInstance.h \
        GUI/FlowLayout.h \
        GUI/InstanceWidget.h \
        Minecraft/Yggdrasil.h \
        Minecraft/AuthSession.h \
        GUI/LoginDialog.h

FORMS += \
        UI/MainWindow.ui \
        UI/SetupDialog.ui \
        UI/PackWidget.ui \
        UI/InstanceWidget.ui \
    UI/LoginDialog.ui

RESOURCES += \
        Assets/icons.qrc
