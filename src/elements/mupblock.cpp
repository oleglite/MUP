#include "mupblock.h"

MupBlock::MupBlock(const QString& label):
    MupElement(label)
{
    type = "Block";
}

QString MupBlock::contentToHtml(){
    QString html = "";

    for(ElementList::ConstIterator pos = childs.begin(); pos!=childs.end(); pos++){
        html+= groupElementOpenTag() + (*pos)->toHtml() + groupElementCloseTag();
    }

    if(getGrouping() == "horizontal")
        return "<table><tr>" + html + "</tr></table>";
    else if(getGrouping() == "vertical")
        return "<table>" + html + "</table>";
    return html;
}

QString MupBlock::tagName(){
    return "div";
}

QString MupBlock::groupElementOpenTag(){
    if(getGrouping() == "horizontal")
        return "<td>";
    else if(getGrouping() == "vertical")
        return "<tr><td>";
    return QString();
}

QString MupBlock::groupElementCloseTag(){
    if(getGrouping() == "horizontal")
        return "</td>";
    else if(getGrouping() == "vertical")
        return "</tr></td>";
    return QString();
}

void MupBlock::addChild(MupElement* child){
    childs.push_back(child);
}

MupElement* MupBlock::findChild(const QString& label){
    foreach(MupElement* element, childs){
        if(element->getLabel()==label)
            return element;
    }
    bool childNotFound = false;
    Q_ASSERT(childNotFound);
    return NULL;
}
