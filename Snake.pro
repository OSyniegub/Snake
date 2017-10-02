#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T12:55:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgamefield.cpp \
    addtorecordtable.cpp \
    bestscores.cpp

HEADERS  += mainwindow.h \
    qgamefield.h \
    addtorecordtable.h \
    bestscores.h

FORMS    += mainwindow.ui \
    addtorecordtable.ui \
    bestscores.ui
