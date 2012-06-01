#ifndef MUPLINK_H
#define MUPLINK_H

#include "muptext.h"

class MupLink : public MupText
{
public:
    MupLink(const QString& label, const QString& ref);

    virtual QString tagName();
    virtual QString tagAttributs();
    virtual bool checkType(const QString &) const;

private:
    QString reference;
};

#endif // MUPLINK_H
