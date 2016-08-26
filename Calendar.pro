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
    ICalManager.cpp \
    CalManager.cpp \
    CalItem.cpp \
    CalFile.cpp \
    CalEvent.cpp \
    CalNote.cpp \
    DayWidget.cpp \
    Calender.cpp \
    EventSettingDialog.cpp \
    DayInfoWidget.cpp

HEADERS  += mainwindow.h \
    calender.h \
    ICalManager.h \
    CalManager.h \
    CalEvent.h \
    CalFile.h \
    CalItem.h \
    CalNote.h \
    DayWidget.h \
    EventSettingDialog.h \
    DayInfoWidget.h \
    calitemall.h \
    windowdrag.h

FORMS    += mainwindow.ui \
    daywidget.ui \
    calender.ui \
    EventSettingDialog.ui \
    DayInfoWidget.ui

CONFIG += c++11
