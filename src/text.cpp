#include "text.h"
#include <QDebug>

Text::Text(){
}

Text::~Text(){
    foreach(TextElement* element, mText){
        delete element;
    }
}

void Text::add(const QString& name, const QString& text, const QStringList& meta){
    TextElement* textElement = new TextElement(text, meta);
    mText.insert(name, textElement);
}

const QString* Text::getText(const QString& name) const{
    return &(mText.find(name).value()->first);
}

bool Text::isEmpty() const{
    return mText.isEmpty();
}

QList<const TextElement*> Text::getElementList() const{
    QList<const TextElement*> elementList;
    foreach(const TextElement* element, mText)
        elementList << element;
    return elementList;
}
