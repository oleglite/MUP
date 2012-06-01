#ifndef MUPLIST_H
#define MUPLIST_H

#include "muptext.h"

class MupList : public MupText
{
public:
    MupList(const QString& label);

protected:
    virtual QString tagName();
    virtual QString groupElementOpenTag();
    virtual QString groupElementCloseTag();
    virtual bool checkType(const QString &) const;
};

#endif // MUPLIST_H
