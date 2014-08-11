#include <QString>
#include <QRegularExpression>
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
    QTextStream stream(&outputfile);
    stream << result;
}

QString process(const QString inputfilename)
{
    QFile inputfile(inputfilename);
    if (!inputfile.open(QIODevice::ReadOnly)) {
        throw Exception(u("Unable to open input file \"%1\" for reading!").arg(inputfilename));
    }

    QString result;
    QTextStream stream(&inputfile);
    int linecounter = 0;
    while (!stream.atEnd()) {
        ++linecounter;
        const QString positionInFile = u("%1:%2").arg(inputfilename).arg(linecounter);
        auto line = stream.readLine();
        const int index = line.indexOf(u("@@snippet("));
        if ( index != -1) {
            const int openingBracket = line.indexOf(u("("), index);
            Q_ASSERT(openingBracket  != 0); // we just searched for it above
            int position = openingBracket;
            int brackets = 1;
            while (brackets != 0) {
                position += 1;
                if (position == line.count()) {
                    throw Exception(u("%1: Syntax error, opening and closing brackets do not match!")
                                    .arg(positionInFile));
                }
                auto const character = line.at(position);
                if (character == QChar::fromLatin1('(')) {
                    brackets += 1;
                } else if (character == QChar::fromLatin1(')')) {
                    brackets -= 1;
                }
            }
            const QString command = line.mid(index, openingBracket - index);
            const QString arguments = line.mid(openingBracket + 1, position - openingBracket - 1);
            if (command == u("@@snippet")) {
                result += process_snippet(arguments, positionInFile);
            } else {
                throw Exception(u("%1: Unknown parser instruction \"%1\" at line %2!").arg(positionInFile).arg(command));
            }
        } else {
            result.append(line + u("\n"));
        }
    }

    return result;
}

QString process_snippet(const QString argumentString, const QString& position)
{
    const QStringList arguments = argumentString.split(u(","));
    if (arguments.count() != 3) {
        throw Exception(u("%1: Argument error!").arg(position));
    }
    const QString filename = arguments[0].trimmed();
    const QString snippet = arguments[1].trimmed();
    const QString style = arguments[2].trimmed();

    QFile sourceFile(filename);
    if (!sourceFile.open(QIODevice::ReadOnly)) {
        throw Exception(u("%1: Error opening file \"%2\" for reading!").arg(position).arg(filename));
    }
    QTextStream stream(&sourceFile);
    int linecounter = 0;
    bool found = false;
    bool reading = false;
    bool complete = false;
    QString result;
    while (!stream.atEnd()) {
        ++linecounter;
        const QString positionInFile = u("%1:%2").arg(filename).arg(linecounter);
        auto line = stream.readLine();
        if (reading) {
            const QRegularExpression snipped_end(u("(\\/\\/|\\#\\#)\\@\\@snippet_end"));
            const int index = line.indexOf(snipped_end);
            if (index == -1) {
                result.append(line + u("\n"));
            } else {
                reading = false;
                result += u("~~~\n");
                complete = true;
                break;
            }
        } else {
            const QRegularExpression snippet_begin(u("(\\/\\/|\\#\\#)\\@\\@snippet_begin\\("));
            const int index = line.indexOf(snippet_begin);
            if (index != -1) {
                const int openingBracket = line.indexOf(u("("), index);
                Q_ASSERT(openingBracket  != 0); // we just searched for it above
                int position = openingBracket;
                int brackets = 1;
                while (brackets != 0) {
                    position += 1;
                    if (position == line.count()) {
                        throw Exception(u("%1: Syntax error, opening and closing brackets do not match!")
                                        .arg(positionInFile));
                    }
                    auto character = line.at(position);
                    if (character == u("(")) {
                        brackets += 1;
                    } else if (character == u(")")) {
                        brackets -= 1;
                    }
                }
                const QString name = line.mid(openingBracket + 1, position - openingBracket - 1);
                if (name == snippet) {
                    reading = true;
                    found = true;
                    const QString opener = u("~~~ {#%1 .%2 .numberLines startFrom=\"%3\"}\n")
                            .arg(snippet)
                            .arg(style)
                            .arg(linecounter + 1);
                    result += opener;
                }
            }
        }
    }
    if (!found) {
        throw Exception(u("%1: Snippet \"%2\" not found!").arg(filename).arg(snippet));
    }
    if (!complete) {
        throw Exception(u("%1: End tag not found for snippet \"%2\"!").arg(filename).arg(snippet));
    }
    return result;
}
