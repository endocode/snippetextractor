TEMPLATE = subdirs
SUBDIRS = extractor.pro tests.pro
CONFIG += ordered

lessThan(QT_MAJOR_VERSION, 5) {
    message("SnippetExtractor requires Qt 5. You are using $${QT_VERSION}.")
    error("Please use Qt 5 to build SnippetExtractor.")
}

OTHER_FILES += \
    sources.pri
