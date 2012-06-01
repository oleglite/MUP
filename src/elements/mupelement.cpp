#include "mupelement.h"
#include <QDebug>

MupElement::MupElement(const QString& label, bool isSingle):
    isSingleTag(isSingle),
    style(QString())
{
    this->label = label;
}

void MupElement::setStyle(QString style){
    grouping = getGroupFromStyle(style);
    this->style = style;
}

QString MupElement::getLabel() const{
    return label;
}

QString MupElement::getStyle() const{
    return style;
}

QString MupElement::getGrouping() const{
    return grouping;
}

QString MupElement::getType() const{
    return type;
}

bool MupElement::checkType(const QString& type) const{
    return this->type == type;
}

QString MupElement::toHtmlAttribute(const QString& name, const QString& value){
    return name+"=\""+value+"\" ";
}

QString MupElement::getGroupFromStyle(QString& style, bool removeOn){
    QString group;
    QString grTag = "group:";
    int grBegin = style.indexOf(grTag);
    if(grBegin >= 0){
        int grEnd = style.indexOf(';');
        group = style.mid( grBegin + grTag.size(),
                              grEnd - (grBegin + grTag.size()) );
        group.remove(' ');
        if(removeOn){
            style.remove(grBegin, grEnd-grBegin+1);
            while(style[0]==' ')
                style.remove(0, 1);
        }
    }
    return group;
}

QString MupElement::toHtml(){
    QString tag = "<" + tagName() + " " + tagAttributs() + ">\n";

    //qDebug() << tag;

    if(!isSingleTag){
        tag += contentToHtml() + "</" + tagName() + ">\n";
    }
    //qDebug() << tag;
    return tag;
}

QString MupElement::tagAttributs(){
    QString attributes;

    if(!getLabel().isEmpty())
        attributes += toHtmlAttribute("id", getLabel());

    //qDebug() << attributes;

    if(!getStyle().isEmpty())
        attributes += toHtmlAttribute("style", getStyle());

    //qDebug() << getStyle() << attributes;

    return attributes;
}
