QT += xml sql
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
main.cpp\
cui.cpp\
csv.cpp \
    csv_storage.cpp \
    xml_storage.cpp \
    sqlite_storage.cpp

HEADERS += \
cui.h\
csv.h\
dino.h\
period.h\
optional.h \
    csv_storage.h \
    storage.h \
    xml_storage.h \
    sqlite_storage.h

DISTFILES += \
data/csv/data.csv \
data/csv/data2.csv \
    data/xml/data.xml \
    data/xml/data2.xml \
data/sql/data.sqlite\
