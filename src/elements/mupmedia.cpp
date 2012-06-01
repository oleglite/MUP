#include "mupmedia.h"

MupMedia::MupMedia(const QString& label, bool isSingle):
    MupElement(label, isSingle)
{
    type = "Media";
}

QString MupMedia::groupElementOpenTag(){
    return QString();
}

QString MupMedia::groupElementCloseTag(){
    return QString();
}
