#include "muploader.h"
#include <QDebug>

PageMarkup* MupLoader::load(const QString& mupSrc, const QString& textSrc){
    // загружаем разметку
    PageMarkup* page = loadPageMarkup(mupSrc);

    // загружаем ей текст
    page->setText(loadPageText(textSrc));

    return page;
}

Text* MupLoader::loadPageText(const QString& source){
    Text* text = new Text(); // освобождаетс€ в PageMarkup::~PageMarkup()

    // разбиваем исходную строку на отдельные элементы
    QStringList list = source.split("\n");

    // регул€рные выражени€ дл€ элементов с метаинформацией и без
    QRegExp simpleRegExp("(\\w+)=\\[(.+)\\]");
    QRegExp metaRegExp("(\\w+)=meta\\((.+)\\)\\+\\[(.+)\\]");

    // из каждого элемента с помощью регул€рных выражений получаем информацию и заносим еЄ в text
    foreach(QString string, list){
        if(string.indexOf(metaRegExp) >= 0){
            metaRegExp.indexIn(string);
            const QStringList& capturedTexts = metaRegExp.capturedTexts();
            text->add(capturedTexts[1], capturedTexts[3], QString(capturedTexts[2]).remove(' ').split(','));
        }else if(string.indexOf(simpleRegExp) >= 0){
            simpleRegExp.indexIn(string);
            const QStringList& capturedTexts = simpleRegExp.capturedTexts();
            text->add(capturedTexts[1], capturedTexts[2], QStringList());
        }else{
            qWarning() << "unexpected line" << string;
        }
    }
    return text;
}

PageMarkup* MupLoader::loadPageMarkup(const QString& source){
    // создаем страницу разметки
    // освобождаетс€ в MainWindow::~MainWindow() и MainWindow::setPage(PageMarkup* page)
    PageMarkup* pageMarkup = new PageMarkup();

    // разбиваем исходник на отдельные элементы
    QStringList sourceList = source.split("\n");
    sourceList.removeAll(QString(""));

    // созадем регул€рное выражение дл€ tag(name)=[arg1, arg2, arg3]+{style}
    QRegExp mupRegExp("(\\w+)\\((\\w+)\\)\\=\\[(.+)\\]\\+\\{(.+)\\}");

    // парсим каждый элемент
    foreach(QString string, sourceList){
        mupRegExp.indexIn(string);
        const QStringList& capturedTexts = mupRegExp.capturedTexts();
        const QStringList& args = spaceFilter(capturedTexts[3]).split(',');
        pageMarkup->addElement(capturedTexts[2], capturedTexts[1], capturedTexts[4], args);
    }
    return pageMarkup;
}

/*
PageMarkup* MupLoader::loadPageMarkup1(const QString& source){
    qDebug()<<"loadMarkup";

    PageMarkup* pageMarkup = new PageMarkup(); // освобождаетс€ в MainWindow::~MainWindow() и MainWindow::setPage(PageMarkup* page)

    int recordBegin = 0;
    int recordEnd = 0;
    const QString& recordDelim = "\r\n";

    while(recordBegin<source.size() && recordEnd<source.size()){
        recordEnd = source.indexOf(recordDelim, recordBegin);
        if(recordEnd<0)
            break;
        Record record = markupParsing(source.mid(recordBegin, recordEnd));
        pageMarkup->addElement(record.label, record.type, record.style, record.args);
        recordBegin = recordEnd+2;
    }
    return pageMarkup;
}

Record MupLoader::markupParsing(const QString& src){
    QString source = src;
    while(!source[0].isLetter())
        source.remove(0, 1);

    int typeOpen = source.indexOf('(');
    int typeClose = source.indexOf(')', typeOpen);
    int argsOpen = source.indexOf('[', source.indexOf('=', typeClose));
    int argsClose = source.indexOf(']', argsOpen);
    int styleOpen = source.indexOf('{', source.indexOf('+', argsClose));
    int styleClose = source.indexOf('}', styleOpen);

    Record record;

    if(styleClose<0)
        return record;

    record.type = spaceFilter(source.mid(0, typeOpen));
    record.label = spaceFilter(source.mid(typeOpen+1, typeClose-typeOpen-1));
    record.args = spaceFilter(source.mid(argsOpen+1, argsClose-argsOpen-1)).split(',');
    record.style = source.mid(styleOpen+1, styleClose-styleOpen-1);

    //qDebug() << record.type << record.label<<record.args<<record.style;

    return record;
}*/

QString MupLoader::spaceFilter(const QString& string){
    QString str = string;
    str.remove(' ');
    str.remove('\t');
    str.remove('\r');
    return str.remove("\n");
}
