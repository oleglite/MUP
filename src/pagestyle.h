#ifndef PAGESTYLE_H
#define PAGESTYLE_H

#include <QString>
#include <QMap>
#include "style.h"

class PageStyle
{
    typedef QMap<QString, QString> StringMap;
    typedef QMap<QString, Style*> StyleMap;

    friend QDebug operator<<(QDebug, const PageStyle&);

public:
    PageStyle();
    ~PageStyle();

    void addStyle(const QString& label, const QString& type, StringMap* attributes, const QString& inherit = 0 );
    void deleteStyle(const QString& label);
    Style* getStyle(const QString& label);

    QString toHtml();

private:
    StyleMap styles;
};

QDebug operator<<(QDebug, const PageStyle&);

#endif // PAGESTYLE_H
