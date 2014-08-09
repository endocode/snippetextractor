#include <QObject>

#include "Helpers.h"

QString u(const char* input) {
    //TODO look up the right way to do this:
    return QObject::trUtf8(input);
}
