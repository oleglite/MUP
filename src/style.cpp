#include "style.h"
#include <QDebug>

Style::Style(const QString& type, StringMap* attributes, Style* inherit)
{
    this->type = type;
    if(inherit!=NULL && this->type == inherit->type){
        this->attributes = inherit->attributes;
    }
    copyWithReplace(this->attributes, *attributes);
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const Style &style)
{
    dbg << "Style(" << style.type <<',' << style.attributes << ')';
    return dbg;
}
#endif

void Style::setAttribute(const QString& name, const QString& value){
    attributes.insert(name, value);
}

QString Style::getAttribute(const QString& name){
    return attributes.value(name, "null");
}

QString Style::getType(){
    return type;
}

void Style::copyWithReplace(StringMap &to, StringMap &from){
    StringMap::Iterator iter = from.begin();
    for(; iter!=from.end(); iter++){
        to.insert(iter.key(), iter.value());
    }
}

QString Style::toCss(){
    QString css;

    if(getType()=="text"){

        if(boolAttribute("bold"))
            css+="font-weight: bold; ";

        if(boolAttribute("underline"))
            css+="text-decoration: underline; ";

        if(boolAttribute("italic"))
            css+="font-style: italic; ";

        if(getAttribute("font-size")!="null")
            css+="font-size: "+getAttribute("font-size")+"; ";

        if(getAttribute("color")!="null")
            css+="color: "+getAttribute("color")+"; ";

        if(getAttribute("text-align")!="null")
            css+="text-align: "+getAttribute("text-align")+"; ";

    }else if(getType()=="block"){

        if(getAttribute("margin")!="null")
            css+="margin: "+getAttribute("margin")+"; ";

    }

    return css;
}

bool Style::boolAttribute(const QString& attr){
    return getAttribute(attr)=="true";
}
