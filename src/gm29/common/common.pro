#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T15:34:18
#
#-------------------------------------------------

QT       += core sql qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = common
TEMPLATE = lib

INCLUDEPATH += ./include
LIBS += -L../../gm29/lib -lcurl -lxl

HEADERS += \
    ccurl.h \
    cexcelreader.h \
    cdaoyouexcelreader.h

SOURCES += \
    ccurl.cpp \
    cexcelreader.cpp \
    cdaoyouexcelreader.cpp

DESTDIR = ../../gm29/bin

CONFIG += qaxcontainer
