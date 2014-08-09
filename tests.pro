QT       += testlib
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = tst_MarkdownFilterTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(sources.pri)

SOURCES += tst_MarkdownFilterTests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
