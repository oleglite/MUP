#include "muplink.h"

MupLink::MupLink(const QString& label, const QString& ref):
    MupText(label),
    reference(ref)
{
    type = "Link";
}

QString MupLink::tagName(){
    return "a";
}

QString MupLink::tagAttributs(){
    return MupText::tagAttributs() + toHtmlAttribute("href", reference);
}

bool MupLink::checkType(const QString& type) const{
    return type == "Text" || this->type == type;
}
