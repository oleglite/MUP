#include "muptext.h"
#include <QDebug>

MupText::MupText(const QString& label):
    MupElement(label)
{
    type = "Text";
    mText = NULL;
}

void MupText::setContent(const QStringList& content){
    mContent = content;
}

void MupText::setText(Text* text){
    mText = text;
}

QString MupText::contentToHtml(){
    Q_ASSERT(mText != NULL && !mText->isEmpty());

    QString html;
    for(QStringList::ConstIterator pos = mContent.begin(); pos != mContent.end(); pos++){
        html += groupElementOpenTag() + *(mText->getText(*pos)) + groupElementCloseTag();
    }
    return html;
}

QString MupText::tagName(){
    return "text";
}

QString MupText::groupElementOpenTag(){
    return "";
}

QString MupText::groupElementCloseTag(){
    return "";
}

