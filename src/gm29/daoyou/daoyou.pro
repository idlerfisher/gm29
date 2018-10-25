#-------------------------------------------------
#
# Project created by QtCreator 2017-06-30T15:12:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = daoyou
TEMPLATE = lib

INCLUDEPATH += ./include

LIBS += -L../../gm29/lib

HEADERS += \
    cdaoyouitemtable.h \
    cdaoyougmui.h

SOURCES += \
    cdaoyouitemtable.cpp \
    cdaoyougmui.cpp

DESTDIR = ../../gm29/bin

FORMS += \
    cdaoyougmui.ui
