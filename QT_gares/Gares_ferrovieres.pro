QT       += core gui widgets qml quick

TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
# CONFIG -= qt

SOURCES += cpp/main.cpp \
    cpp/wmanager.cpp \
    cpp/utile.cpp \
    cpp/table.cpp

HEADERS += \
    cpp/wmanager.h \
    cpp/utile.h \
    cpp/table.h

DISTFILES += \
    qml/main.qml \
    qml/content/MyScript.js
