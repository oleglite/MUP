#ifndef MUPPICTURE_H
#define MUPPICTURE_H

#include "mupmedia.h"

class MupPicture : public MupMedia
{
public:
    MupPicture(const QString& label, const QString& ref);

    virtual QString contentToHtml();
    virtual QString tagName();
    virtual QString tagAttributs();

private:
    QString reference;
};

#endif // MUPPICTURE_H
