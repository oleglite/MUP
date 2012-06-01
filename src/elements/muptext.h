#ifndef MUPTEXT_H
#define MUPTEXT_H

#include <elements/mupelement.h>
#include <text.h>

class MupText : public MupElement
{
public:
    MupText(const QString& label);

    void setContent(const QStringList& content);
    void setText(Text* text);

protected:
    virtual QString contentToHtml();
    virtual QString tagName();
    virtual QString groupElementOpenTag();
    virtual QString groupElementCloseTag();

protected:
    QStringList mContent;
    Text* mText;
};

#endif // MUPTEXT_H
