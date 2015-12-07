#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T12:45:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_app
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    boardsquare.cpp \
    board.cpp \
    gamecontroller.cpp \
    playwindow.cpp \
    loadedgamewindow.cpp \
    loadwindowcontroller.cpp

HEADERS  += mainwindow.h \
    boardsquare.h \
    board.h \
    figures.h \
    gamecontroller.h \
    playwindow.h \
    loadedgamewindow.h \
    loadwindowcontroller.h \
    step.h

FORMS    += \
    playwindow.ui \
    loadedgamewindow.ui \
    mainwindow.ui

RESOURCES += \
    resources.qrc
