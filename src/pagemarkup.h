#ifndef PAGEMARKUP_H
#define PAGEMARKUP_H

//#include "mupElements.h"
#include <QtCore>
#include "text.h"
#include "elements/mupelement.h"
#include "elements/muptext.h"
#include "elements/muplink.h"
#include "elements/muplist.h"
#include "elements/mupblock.h"
#include "elements/muppicture.h"

class PageMarkup
{
public:
    typedef QList<MupElement*> ElementList;
    typedef QMap<QString, QString> StringMap;

    const QString MAIN_ELEMENT_LABEL;

public:
    PageMarkup();
    ~PageMarkup();

    void setText(Text* mText);

    QString toHtml() const;

    //! добавить элемент разметки
    void addElement(const QString& label, const QString& type, const QString& style, const QStringList& args);

    //! создать текстовый элемент
    void createTextElement(const QString& label, const QString& text, const QString& style, const QStringList& meta, const QString& link = QString());

private:
    MupElement* newText(const QString& label,
                        const QString& style,
                        const QStringList& args) const;

    MupElement* newBlock(const QString& label,
                         const QString& style,
                         const QStringList& args) const;

    MupElement* newMedia(const QString& label,
                         const QString& style,
                         const QStringList& args) const;

    MupElement* findElement(const QString& label) const;

private:
    ElementList mBodyElements;
    Text* mText;
};

#endif // PAGEMARKUP_H
