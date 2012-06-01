#include "pagestyle.h"

PageStyle::PageStyle()
{
}

PageStyle::~PageStyle()
{
    foreach(Style* style, styles){
        delete style;
    }
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const PageStyle &pageStyle)
{
    dbg << "PageStyle(" << endl;
    for(PageStyle::StyleMap::ConstIterator pos = pageStyle.styles.begin(); pos!=pageStyle.styles.end(); pos++){
        dbg << '\t' << pos.key() << *pos.value() << endl;
    }
    dbg << ')';
    return dbg;
}
#endif

void PageStyle::addStyle(const QString& label, const QString& type, StringMap* attributes, const QString& inherit){
    Style* inheritStyle = NULL;
    StyleMap::Iterator inheritPosition = styles.find(inherit);
    if(inheritPosition!=styles.end()){
        inheritStyle = inheritPosition.value();
    }
    Style* style = new Style(type, attributes, inheritStyle);
    styles.insert(label, style);
}

void PageStyle::deleteStyle(const QString& label){
    StyleMap::iterator pos = styles.find(label);
    if(pos!=styles.end()){
        delete pos.value();
        styles.erase(pos);
    }
}

Style* PageStyle::getStyle(const QString& label){
    StyleMap::iterator pos = styles.find(label);
    if(pos!=styles.end()){
        return pos.value();
    }else{
        return NULL;
    }
}

QString PageStyle::toHtml(){
    QString html = "<style type=\"text/css\">\n";
    for(StyleMap::Iterator pos = styles.begin(); pos!=styles.end(); pos++){
        if(!pos.key().isEmpty())
            html += "\t#"+pos.key()+" {"+pos.value()->toCss()+"}\n";
    }
    html+="</style>\n";
    return html;
}
