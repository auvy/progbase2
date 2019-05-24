#-------------------------------------------------
#
# Project created by QtCreator 2019-05-01T20:54:04
#
#-------------------------------------------------

QT       += core gui
QT += xml
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab9
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

SUBDIRS += \
    lab9.pro

FORMS += \
    add_d.ui \
    add_p.ui \
    edit_d.ui \
    edit_p.ui \
    mainwindow.ui \
    auth.ui

DISTFILES += \
    sql/data.sqlite \
    data.sqlite \
    sqldata.sqlite

HEADERS += \
    add_d.h \
    add_p.h \
    csv.h \
    csv_storage.h \
    dino.h \
    edit_d.h \
    edit_p.h \
    mainwindow.h \
    optional.h \
    period.h \
    sqlite_storage.h \
    storage.h \
    user.h \
    xml_storage.h \
    auth.h

SOURCES += \
    add_d.cpp \
    add_p.cpp \
    csv.cpp \
    csv_storage.cpp \
    dino.cpp \
    edit_d.cpp \
    edit_p.cpp \
    main.cpp \
    mainwindow.cpp \
    period.cpp \
    sqlite_storage.cpp \
    xml_storage.cpp \
    user.cpp \
    dialog.cpp \
    auth.cpp
