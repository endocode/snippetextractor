#include <QString>

#include "Helpers.h"
#include "Process.h"
#include "Exception.h"

void process( const QString inputfile, const QString outputfile) {
    throw Exception(u("%1: Not implemented").arg(Q_FUNC_INFO));
}
