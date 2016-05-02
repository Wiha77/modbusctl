#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T16:35:26
#
#-------------------------------------------------

CONFIG += link_pkgconfig
PKGCONFIG += libmodbus

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = modbusctl
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    mod_poller.cpp

HEADERS  += dialog.h \
    mod_poller.h

FORMS    += dialog.ui
