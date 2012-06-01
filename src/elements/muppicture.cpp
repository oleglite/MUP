#include "muppicture.h"

MupPicture::MupPicture(const QString& label, const QString& ref):
    MupMedia(label, true),
    reference(ref)
{
    type = "Picture";
}

QString MupPicture::contentToHtml(){
    return QString();
}

QString MupPicture::tagName(){
    return "img";
}

QString MupPicture::tagAttributs(){
    return MupElement::tagAttributs() + toHtmlAttribute("src", reference);;
}
