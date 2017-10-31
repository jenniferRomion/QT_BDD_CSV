QT       += core gui widgets qml quick sql

TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
# CONFIG -= qt

SOURCES += cpp/main.cpp \
    cpp/wmanager.cpp \
    cpp/utile.cpp \
    cpp/table.cpp \
    cpp/sqluser.cpp \

HEADERS += \
    cpp/wmanager.h \
    cpp/utile.h \
    cpp/table.h \
    cpp/sqluser.h \

DISTFILES += \
    qml/main.qml \
    qml/content/MyScript.js \
    qml/LoadData.qml \
    qml/content/images/logo.jpg \
    qml/content/images/help.jpg \
    qml/MyButton.qml \
    qml/help.qml \
    qml/gbdb.qml
