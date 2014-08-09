QT       += core

QT       -= gui

QMAKE_CXXFLAGS += -std=c++11

TARGET = markdownfilter
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Exception.cpp \
    Helpers.cpp \
    Process.cpp

HEADERS += \
    Exception.h \
    Helpers.h \
    Process.h
