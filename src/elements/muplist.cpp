#include "muplist.h"
#include <QDebug>

MupList::MupList(const QString& label):
    MupText(label)
{
    type = "List";
}

QString MupList::tagName(){
    //qDebug() << getGrouping();
    if(getGrouping().toLower() == "bulletedlist")
        return "ul";
    if(getGrouping().toLower() == "numericlist")
        return "ol";
    return "";
}

QString MupList::groupElementOpenTag(){
    return "<li>";
}

QString MupList::groupElementCloseTag(){
    return "</li>";
}

bool MupList::checkType(const QString& type) const{
    return type == "Text" || this->type == type;
}
