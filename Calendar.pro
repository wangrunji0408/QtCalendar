#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T11:01:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    daywidget.cpp \
    calender.cpp \
    calendarmanager.cpp \
    calevent.cpp \
    calfile.cpp \
    calnote.cpp \
    calitem.cpp

HEADERS  += mainwindow.h \
    daywidget.h \
    calender.h \
    calendarmanager.h \
    calevent.h \
    calfile.h \
    calnote.h \
    calitem.h

FORMS    += mainwindow.ui \
    daywidget.ui \
    calender.ui

CONFIG += c++11
