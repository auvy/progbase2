#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T20:49:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab7
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
        mainwindow.cpp \
    csv.cpp \
    csv_storage.cpp \
    period.cpp \
    dino.cpp \
    add_d.cpp \
    add_p.cpp \
    edit_d.cpp \
    edit_p.cpp

HEADERS += \
        mainwindow.h \
#    xml_storage.h
    optional.h \
    period.h \
    storage.h \
    dino.h \
    csv.h \
    csv_storage.h \
    add_d.h \
    add_p.h \
    edit_d.h \
    edit_p.h

FORMS += \
        mainwindow.ui \
    add_d.ui \
    add_p.ui \
    edit_d.ui \
    edit_p.ui

DISTFILES += \
    data/xml/data.xml \
    data/xml/data2.xml \
    data/csv/data.csv \
    data/csv/data2.csv
