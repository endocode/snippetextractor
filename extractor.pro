QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = snippetextractor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
target.path = /usr/local/bin
INSTALLS += target

include(sources.pri)

SOURCES += main.cpp
