#ifndef MUPMEDIA_H
#define MUPMEDIA_H

#include "mupelement.h"

class MupMedia : public MupElement
{
public:
    MupMedia(const QString& label, bool isSingle = false);

protected:
    virtual QString groupElementOpenTag();
    virtual QString groupElementCloseTag();
};

#endif // MUPMEDIA_H
