QT       += testlib
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = tst_SnippetExtractorTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(sources.pri)

SOURCES += tst_SnippetExtractorTests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

RESOURCES += \
    TestResources.qrc
