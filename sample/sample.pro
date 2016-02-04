#-------------------------------------------------
#
# Project created by QtCreator 2016-02-01T22:11:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

TARGET = sample
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qscale.cpp \
    abstractmeter.cpp \
    manometer.cpp \
    widgetwithbackground.cpp

HEADERS  += widget.h \
    qscale.h \
    abstractmeter.h \
    manometer.h \
    widgetwithbackground.h \
    functions.h

FORMS    += widget.ui
