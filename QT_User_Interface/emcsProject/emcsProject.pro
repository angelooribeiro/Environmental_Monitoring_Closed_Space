#-------------------------------------------------
#
# Project created by QtCreator 2017-01-16T16:17:42
#
#-------------------------------------------------

QT += core
QT += gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emcsProject
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += main.cpp\
        mainwindow.cpp \
    cprmdialog.cpp \
    cdatabase.cpp \
    readdialog.cpp \
    calertdialog.cpp

HEADERS  += mainwindow.h \
    cprmdialog.h \
    cdatabase.h \
    parameters.h \
    readdialog.h \
    calertdialog.h

FORMS    += mainwindow.ui \
    cprmdialog.ui \
    readdialog.ui \
    calertdialog.ui

DISTFILES += \
    logo.PNG
