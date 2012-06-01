#ifndef SEARCHGENERATOR_H
#define SEARCHGENERATOR_H

#include <QtCore>
#include "pagemarkup.h"

// ���� �������������(0...1000), �����
typedef QPair<int, const QString*> SearchResultElement;

typedef QPair<QString, SearchResultElement> StringResultPair;
typedef QList<StringResultPair> StringResultList;

class SearchGenerator
{
    //! ���������� ����������� ������������� ����������� ������.
    static const int LEAST_RELEVANCE = 1;

public:
    SearchGenerator(const QString& request);

    PageMarkup* getResultPage();

    void search(Text* text, const QString& filename);

    //! ��������� ������ �� �����.
    static QStringList splitForWords(const QString& string);

    static int calculateRelevance(const QStringList&, const TextElement*);

private:
    //! ��������� ������.
    QString mRequest;

    //! ��������� ������ � ���� ��������� ����.
    QStringList mRequestWords;

    //! ��������� ������ � ���� ��� ���� - ��������� �������.
    StringResultList mSearchResults;

    //! ��������� �� �������� @p page ���� � ���������� ������ � ������� @p number, @return �������� �����.
    QString addSearchResultElement(PageMarkup* page,
                                   int number,
                                   const QString& file,
                                   const SearchResultElement* resultElement);
};

#endif // SEARCHGENERATOR_H
