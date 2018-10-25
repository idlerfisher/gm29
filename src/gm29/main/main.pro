#-------------------------------------------------
#
# Project created by QtCreator 2017-06-17T15:34:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = gm29
TEMPLATE = app

INCLUDEPATH += ../common \
               ../common/include \
               ../daoyou

LIBS += -L../../gm29/lib \
        -L../../gm29/bin \
        -lcommon \
        -ldaoyou

SOURCES += main.cpp \
    cicadamainwindow.cpp

HEADERS  += \
    cicadamainwindow.h

FORMS    += cicadamainwindow.ui

DESTDIR = ../../gm29/bin

RESOURCES += \
    images.qrc

RC_FILE = images/cicada.rc
