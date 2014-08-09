#ifndef PROCESS_H
#define PROCESS_H

class QString;

QString process(const QString inputfilename);
void process(const QString inputfilename, const QString outputfilename);

QString process_snippet(const QString argumentString, const QString &position);

#endif // PROCESS_H
