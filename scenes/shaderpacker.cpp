#include "shaderpacker.h"
#include <QString>
QString SimpleVertex::toString()
{
    QString str("SimpleVertex (%1,%2,%3) texture (%4,%5)");
    str=str.arg(vertAttr.x()).arg(vertAttr.y()).arg(vertAttr.z()).arg(texCoord.x()).arg(texCoord.y());
    return str;
}
