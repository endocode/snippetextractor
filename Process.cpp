#include <QString>
#include <QFile>
#include <QTextStream>

#include "Helpers.h"
#include "Process.h"
#include "Exception.h"

void process( const QString inputfilename, const QString outputfilename) {
    QFile inputfile(inputfilename);
    if (!inputfile.open(QIODevice::ReadOnly)) {
        throw Exception(u("Unable to open input file \"%1\" for reading!").arg(inputfilename));
    }
    QFile outputfile(outputfilename);
    if (!outputfile.open(QIODevice::WriteOnly)) {
        throw Exception(u("Unable to open output file \"%1\" for writing!").arg(outputfilename));
    }

    QTextStream stream(&inputfile);
    while (!stream.atEnd()) {
        auto line = stream.readLine();
    }
}
