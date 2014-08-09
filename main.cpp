/* This file is part of the Tome of Concurrency book.
 * (C) Mirko Boehm <mirko@kde.org>
 * Licensed under the GPLv3.
 */

#include <iostream>

#include <QCoreApplication>
#include <QFileInfo>

#include "Exception.h"
#include "Helpers.h"

//temp:
void process( const QString inputfile, const QString outputfile) {
    throw Exception(u("%1: Not implemented").arg(Q_FUNC_INFO));
}

int main(int argc, char *argv[])
{
    using namespace std;
    try {
        QCoreApplication a(argc, argv);
        const QString copyrightnote = u("%1 - process special instructions in markdown articles to include code samples\n"
                                        "* Author: Mirko Boehm <mirko@kde.org>\n"
                                        "* Licensed under the GPLv3.").arg(a.applicationName());
        std::wcout << copyrightnote.toStdWString() << endl;
        if (argc != 3) {
            const QString usage = u(
                        "\nUsage:\n"
                        "%1 <inputfile> <outputfile>\n").arg(a.applicationName());
            throw Exception(usage);
        }
        const QString inputfile = QString::fromLocal8Bit(argv[1]);
        const QString outputfile = QString::fromLocal8Bit(argv[2]);
        process(inputfile, outputfile);
    } catch(const Exception& ex) {
        wcout << ex.message().toStdWString() <<endl;
    }
}
