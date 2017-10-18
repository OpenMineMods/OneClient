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
        getMemorySize.c \
        Minecraft/MinecraftVersions.cpp \
    libraries/quazip/quazip/JlCompress.cpp \
    libraries/quazip/quazip/qioapi.cpp \
    libraries/quazip/quazip/quaadler32.cpp \
    libraries/quazip/quazip/quacrc32.cpp \
    libraries/quazip/quazip/quagzipfile.cpp \
    libraries/quazip/quazip/quaziodevice.cpp \
    libraries/quazip/quazip/quazip.cpp \
    libraries/quazip/quazip/quazipdir.cpp \
    libraries/quazip/quazip/quazipfile.cpp \
    libraries/quazip/quazip/quazipfileinfo.cpp \
    libraries/quazip/quazip/quazipnewinfo.cpp \
    libraries/quazip/quazip/unzip.c \
    libraries/quazip/quazip/zip.c

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
        getMemorySize.h \
        Minecraft/MinecraftVersions.h \
        Minecraft/MojangInfo.h \
    libraries/quazip/quazip/crypt.h \
    libraries/quazip/quazip/ioapi.h \
    libraries/quazip/quazip/JlCompress.h \
    libraries/quazip/quazip/quaadler32.h \
    libraries/quazip/quazip/quachecksum32.h \
    libraries/quazip/quazip/quacrc32.h \
    libraries/quazip/quazip/quagzipfile.h \
    libraries/quazip/quazip/quaziodevice.h \
    libraries/quazip/quazip/quazip.h \
    libraries/quazip/quazip/quazip_global.h \
    libraries/quazip/quazip/quazipdir.h \
    libraries/quazip/quazip/quazipfile.h \
    libraries/quazip/quazip/quazipfileinfo.h \
    libraries/quazip/quazip/quazipnewinfo.h \
    libraries/quazip/quazip/unzip.h \
    libraries/quazip/quazip/zip.h

FORMS += \
        UI/MainWindow.ui \
        UI/SetupDialog.ui \
        UI/PackWidget.ui \
        UI/InstanceWidget.ui \
    UI/InstanceWindow.ui

RESOURCES += \
        Assets/icons.qrc

DISTFILES += \
    libraries/quazip/NEWS.txt \
    libraries/quazip/CMakeLists.txt \
    libraries/quazip/COPYING

LIBS+=-lz
