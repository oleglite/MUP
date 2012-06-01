#include "pagemarkup.h"
#include <QDebug>

PageMarkup::PageMarkup():
    MAIN_ELEMENT_LABEL(QString("main")){
    mText = new Text; // освобождается в PageMarkup::~PageMarkup()
}

PageMarkup::~PageMarkup(){
    foreach(MupElement* element, mBodyElements){
        delete element;
    }
    delete mText;
}

void PageMarkup::setText(Text *text){
    if(mText)
        delete mText;
    mText = text;
    foreach(MupElement* element, mBodyElements){
        if(element->checkType("Text")){
            MupText* textElement = dynamic_cast<MupText*>(element);
            textElement->setText(text);
        }
    }
}

void PageMarkup::addElement(const QString& label,
                            const QString& type,
                            const QString& style,
                            const QStringList& args){
    if(type.toLower() == "text"){
        mBodyElements.push_back(newText(label, style, args));
    }else if(type.toLower() == "block"){
        mBodyElements.push_back(newBlock(label, style, args));
    }else if(type.toLower() == "media"){
        mBodyElements.push_back(newMedia(label, style, args));
    }
}

MupElement* PageMarkup::newText(const QString& label,
                                const QString& style,
                                const QStringList& args) const{
    MupText* el;
    QString lStyle = style;
    QStringList lArgs = args;

    QString group = MupElement::getGroupFromStyle(lStyle, false);
    if(group == "link"){
        Q_ASSERT(!lArgs.isEmpty());
        el = new MupLink(label, lArgs[0]);
        lArgs.removeFirst();
    }else if(group.endsWith("list")){
        el = new MupList(label);
    }else{
        el = new MupText(label);
    }

    el->setStyle(lStyle);
    el->setContent(lArgs);
    el->setText(mText);

    return el;
}

MupElement* PageMarkup::newBlock(const QString& label,
                                 const QString& style,
                                 const QStringList& args) const{
    MupBlock* block = new MupBlock(label);
    block->setStyle(style);
    for(QStringList::ConstIterator pos = args.begin(); pos != args.end(); pos++){
        MupElement* child = findElement(*pos);
        if(child)
            block->addChild(child);
    }
    return block;
}

MupElement* PageMarkup::newMedia(const QString& label,
                                 const QString& style,
                                 const QStringList& args) const{
    MupMedia* media = NULL;
    if(args[0].endsWith(".jpg")){
        Q_ASSERT(!args.isEmpty());
        media = new MupPicture(label, args[0]);
        media->setStyle(style);
    }
    return media;
}

QString PageMarkup::toHtml() const{
    foreach(MupElement* element, mBodyElements){
        Q_ASSERT(element != NULL);
        if(element->getLabel() == MAIN_ELEMENT_LABEL)
            return element->toHtml();
    }
    return "";
}

MupElement* PageMarkup::findElement(const QString& label) const{
    foreach(MupElement* element, mBodyElements){
        if(element->getLabel() == label)
            return element;
    }
    qDebug() << label;
    Q_ASSERT_X(false, "", "Element not found");
    return NULL;
}

void PageMarkup::createTextElement(const QString& label, const QString& text, const QString& style, const QStringList& meta, const QString& link){
    if(link == QString())
        addElement(label, "Text", style, QStringList() << label);
    else
        addElement(label, "Text", style, QStringList() << link << label);
    mText->add(label, text, meta);
}
