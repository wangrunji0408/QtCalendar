#-------------------------------------------------
#
# Project created by QtCreator 2016-08-24T11:01:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calendar
TEMPLATE = app


SOURCES += \
    CalManager/CalItem/CalEvent.cpp \
    CalManager/CalItem/CalFile.cpp \
    CalManager/CalItem/CalItem.cpp \
    CalManager/CalItem/CalNote.cpp \
    CalManager/CalManager.cpp \
    CalManager/ICalManager.cpp \
    GUI/Dialog/deleventdialog.cpp \
    GUI/Dialog/EventSettingDialog.cpp \
    GUI/Dialog/settingdialog.cpp \
    GUI/EventFilter/filedragouteventfilter.cpp \
    GUI/EventFilter/windowdrageventfilter.cpp \
    GUI/ListItem/listitemevent.cpp \
    GUI/ListItem/listitemfile.cpp \
    GUI/Calender.cpp \
    GUI/DayInfoWidget.cpp \
    GUI/DayWidget.cpp \
    main.cpp

HEADERS  += \
    CalManager/CalItem/calevent.h \
    CalManager/CalItem/calfile.h \
    CalManager/CalItem/CalItem.h \
    CalManager/CalItem/calitemall.h \
    CalManager/CalItem/calnote.h \
    CalManager/CalManager.h \
    CalManager/ICalManager.h \
    GUI/Dialog/deleventdialog.h \
    GUI/Dialog/EventSettingDialog.h \
    GUI/Dialog/settingdialog.h \
    GUI/EventFilter/filedragouteventfilter.h \
    GUI/EventFilter/windowdrageventfilter.h \
    GUI/ListItem/listitemevent.h \
    GUI/ListItem/listitemfile.h \
    GUI/calender.h \
    GUI/DayInfoWidget.h \
    GUI/DayWidget.h \
    Old/windowdrag.h

FORMS    += \
    GUI/Dialog/deleventdialog.ui \
    GUI/Dialog/EventSettingDialog.ui \
    GUI/Dialog/settingdialog.ui \
    GUI/ListItem/listitemevent.ui \
    GUI/ListItem/listitemfile.ui \
    GUI/calender.ui \
    GUI/DayInfoWidget.ui \
    GUI/daywidget.ui

CONFIG += c++11

RESOURCES += \
    res.qrc
