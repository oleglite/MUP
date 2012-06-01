#ifndef MUPBLOCK_H
#define MUPBLOCK_H

#include "mupelement.h"
#include <QList>

class MupBlock : public MupElement
{
public:
    typedef QList<MupElement*> ElementList;

public:
    MupBlock(const QString& label);

    void addChild(MupElement* child);
    MupElement* findChild(const QString& label);

protected:
    virtual QString contentToHtml();
    virtual QString tagName();
    virtual QString groupElementOpenTag();
    virtual QString groupElementCloseTag();

private:
    ElementList childs;
};

#endif // MUPBLOCK_H
