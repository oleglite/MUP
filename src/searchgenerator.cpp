#include "searchgenerator.h"

bool relevanceCompare(const StringResultPair& pair1, const StringResultPair& pair2){
    return pair1.second.first > pair2.second.first;
}

SearchGenerator::SearchGenerator(const QString& request){
    mRequest = request;
    mRequestWords = splitForWords(request);
}

void SearchGenerator::search(Text* text, const QString& filename){
    foreach(const TextElement* element, text->getElementList()){
        int relevance = calculateRelevance(mRequestWords, element);
        if(relevance >= LEAST_RELEVANCE){
            //qDebug() << filename << relevance << element->first;
            const SearchResultElement& resEl = SearchResultElement(relevance, &((*element).first));
            mSearchResults << StringResultPair(filename, resEl);
            qDebug() << mSearchResults;
        }
    }
}

QStringList SearchGenerator::splitForWords(const QString& string){
    QRegExp wordsRegExp("(\\w+)");
    wordsRegExp.indexIn(string);

    QStringList list;
    int pos = 0;

    while ((pos = wordsRegExp.indexIn(string, pos)) != -1) {
        list << wordsRegExp.cap(1);
        pos += wordsRegExp.matchedLength();
    }
    return list;
}

int SearchGenerator::calculateRelevance(const QStringList& requestWords, const TextElement* element){
    qDebug() << "calculateRelevance";
    // считаем сколько мета слов есть в запросе
    int metaMatches = 0;
    foreach(QString metaWord, element->second){
        if(requestWords.contains(metaWord, Qt::CaseInsensitive))
            metaMatches++;
    }

    // считаем сколько слов из запроса, кроме метаслов, есть в тексте
    int textMatches = 0;
    foreach(QString requestWord, requestWords){
        if(element->first.indexOf(requestWord, 0, Qt::CaseInsensitive) >= 0 && !element->second.contains(requestWord))
            textMatches++;
    }

    // считаем и возращаем релевантность
    if(element->second.size() > 0)
        return 1000 * ( 1.1 * (float)metaMatches / element->second.size() + 0.9 * (float)textMatches / requestWords.size() ) / 2;
    else
        return 1000 * 0.9 * (float)textMatches / requestWords.size() / 2;
}

PageMarkup* SearchGenerator::getResultPage(){
    qDebug() << "getResultPage";
    PageMarkup* page = new PageMarkup(); // освобождается в MainWindow::~MainWindow() и MainWindow::setPage(PageMarkup* page)
    page->createTextElement("SearchLabel",
                            QObject::tr("Результаты поиска по запросу ") + "\"" + mRequest + "\"",
                            "font-size: 21px; color: black; font-weight: bold;",
                            QStringList() << QObject::tr("поиск") << QObject::tr("заголовок"));

    page->addElement("SearchLabelBlock",
                     "Block",
                     "margin: 20px; text-align: center;",
                     QStringList() << "SearchLabel");

    QStringList resultBlockArgs;

    qSort(mSearchResults.begin(), mSearchResults.end(), relevanceCompare);

    for(int i = 0; i < mSearchResults.size(); i++)
        resultBlockArgs << addSearchResultElement(page, i, mSearchResults.value(i).first, &mSearchResults.value(i).second);

    page->addElement("SearchResultBlock",
                     "Block",
                     "margin: 20px; text-align: left;",
                     resultBlockArgs);

    page->addElement("main",
                     "Block",
                     "group: vertical; padding: 20px; border: 1px brown solid; background: #fffcfc; margin: 40px;",
                     QStringList() << "SearchLabelBlock" << "SearchResultBlock");
    return page;
}


QString SearchGenerator::addSearchResultElement(PageMarkup* page, int number, const QString& file, const SearchResultElement* resultElement){
    qDebug() << "addSearchResultElement";
    const QString& label = "ResultBlock" + QString::number(number);
    int relevance = resultElement->first;
    page->createTextElement("Text"+label,
                            QString::number(relevance) + ": " + *resultElement->second,
                            "font-size: 16px;",
                            QStringList() << QObject::tr("поиск") << QObject::tr("результат"));

    page->createTextElement("Link" + label,
                            QObject::tr("найдено в ") + file,
                            "group: link;",
                            QStringList() << QObject::tr("поиск") << QObject::tr("ссылка"),
                            file);

    QString background;
    if(relevance >= 300 && relevance < 400)
        background = "background: #fff0f0;";
    else if(relevance >= 400 && relevance < 500)
        background = "background: #ffe0e0;";
    else if(relevance >= 500)
        background = "background: #ffd0d0;";

    page->addElement(label,
                     "Block",
                     "padding: 10px; margin-bottom: 10px; border: 1px dashed black; " + background,
                     QStringList() << "Text"+label << "Link"+label);

    return label;
}
