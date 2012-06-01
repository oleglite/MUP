#ifndef SEARCHGENERATOR_H
#define SEARCHGENERATOR_H

#include <QtCore>
#include "pagemarkup.h"

// пара релевантность(0...1000), текст
typedef QPair<int, const QString*> SearchResultElement;

typedef QPair<QString, SearchResultElement> StringResultPair;
typedef QList<StringResultPair> StringResultList;

class SearchGenerator
{
    //! Минимально необходимая релевантность результатов поиска.
    static const int LEAST_RELEVANCE = 1;

public:
    SearchGenerator(const QString& request);

    PageMarkup* getResultPage();

    void search(Text* text, const QString& filename);

    //! Разделяет строку на слова.
    static QStringList splitForWords(const QString& string);

    static int calculateRelevance(const QStringList&, const TextElement*);

private:
    //! Поисковый запрос.
    QString mRequest;

    //! Поисковый запрос в виде отдельных слов.
    QStringList mRequestWords;

    //! Результат поиска в виде пар файл - найденный элемент.
    StringResultList mSearchResults;

    //! Добавляет на страницу @p page блок с резултатом поиска с номером @p number, @return название блока.
    QString addSearchResultElement(PageMarkup* page,
                                   int number,
                                   const QString& file,
                                   const SearchResultElement* resultElement);
};

#endif // SEARCHGENERATOR_H
