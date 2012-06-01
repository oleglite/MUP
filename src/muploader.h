#ifndef MUPLOADER_H
#define MUPLOADER_H

#include <QtCore>
#include "pagemarkup.h"

class Text;

class Record{
public:
    QString type;
    QString label;
    QStringList args;
    QString style;
};

//! �����, ���������� ������ �������� mup ����������
class MupLoader
{
public:
    //! �������� ��������� �� ����������
    static PageMarkup* load(const QString& mupSrc, const QString& textSrc);

    //! �������� ������� Text �� ���������
    static Text* loadPageText(const QString& source);

    //! �������� �������� �� ����������
    static PageMarkup* loadPageMarkup(const QString& source);
    //static PageMarkup* loadPageMarkup1(const QString& source);

private:
    //static Record markupParsing(const QString&);
    static QString spaceFilter(const QString&);
};

#endif // MUPLOADER_H
