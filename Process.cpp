#include <QString>
#include <QFile>
#include <QTextStream>

#include "Helpers.h"
#include "Process.h"
#include "Exception.h"

void process( const QString inputfilename, const QString outputfilename) {
    const QString result = process(inputfilename);
    QFile outputfile(outputfilename);
    if (!outputfile.open(QIODevice::WriteOnly)) {
        throw Exception(u("Unable to open output file \"%1\" for writing!").arg(outputfilename));
    }

}


QString process(const QString inputfilename)
{
    QFile inputfile(inputfilename);
    if (!inputfile.open(QIODevice::ReadOnly)) {
        throw Exception(u("Unable to open input file \"%1\" for reading!").arg(inputfilename));
    }

    QString result;
    QTextStream stream(&inputfile);
    while (!stream.atEnd()) {
        auto line = stream.readLine();
        result.append(line);
    }

    return result;
}
